Control.Print.printDepth := 100;
exception InvalidInput;
CM.make "sources.cm";
open PredLogic;

fun Occurs(Variable(x),Variable(y))=(x=y)
	|Occurs(Variable(x),AND(p,q)) = Occurs(Variable(x),p) orelse Occurs(Variable(x),q)
	|Occurs(Variable(x),OR(p,q)) = Occurs(Variable(x),p) orelse Occurs(Variable(x),q)
	|Occurs(Variable(x),IMPLY(p,q)) = Occurs(Variable(x),p) orelse Occurs(Variable(x),q)
	|Occurs(Variable(x),DOUBLEIMPLY(p,q)) = Occurs(Variable(x),p) orelse Occurs(Variable(x),q)
	|Occurs(Variable(x),FORALL(a,b)) = Occurs(Variable(x),b)
	|Occurs(Variable(x),EXISTS(a,b)) = Occurs(Variable(x),b)
	|Occurs(Variable(x),FUNCTION(b,c)) = OccursList(Variable(x),c)
	|Occurs(_,_)=false
and OccursList(x,[])= false
	|OccursList(x,l::ls) = Occurs(x,l) orelse OccursList(x,ls)
;

fun CheckUnify(Variable(x),Variable(y))= true
	|CheckUnify(Constant(x),Variable(y))= true
	|CheckUnify(Variable(y),Constant(x))= true
	|CheckUnify(FUNCTION(x,y),FUNCTION(a,b)) = 
		if (x=a) then CheckUnifyList(y,b)
		else false
	|CheckUnify(Variable(x),FUNCTION(a,b)) = 
		if (OccursList(Variable(x),b)) then false
		else true
	|CheckUnify(FUNCTION(a,b),Variable(x)) = 
		if (OccursList(Variable(x),b)) then false
		else true
	|CheckUnify(_,_) = false

and CheckUnifyList([],[])= true
	|CheckUnifyList(x::xs,y::ys) = CheckUnify(x,y) andalso CheckUnifyList(xs,ys) 
	|CheckUnifyList(_,_) = false
;

fun CheckComplimentary(x,NOT(y)) = CheckUnify(x,y)
	|CheckComplimentary(NOT(x),y) = CheckUnify(x,y)
	|CheckComplimentary(_,_) = false
;

fun CheckCompList(x,[])=false
	|CheckCompList(x,y::ys)= CheckComplimentary(x,y) orelse CheckCompList(x,ys)
;

fun CheckComp([])=false
	|CheckComp([x])=false
	|CheckComp(x::xs)=CheckCompList(x,xs) orelse CheckComp(xs)
;

fun JoinOne(a,[])=[]
	|JoinOne(a,x::xs)= List.concat([a,x])::JoinOne(a,xs)
;

fun JoinAll([],xs)=[]
	|JoinAll(x::xs,y)=List.concat([JoinOne(x,y),JoinAll(xs,y)])
;

fun Subs(x,y,Variable(p))= if (x=p) then y else Variable(p)
	|Subs(x,y,Constant(p)) = Constant(p)
	|Subs(x,y,FUNCTION(a,b)) = FUNCTION(a,SubsList(x,y,b))
	|Subs(x,y,AND(p,q)) = AND(Subs(x,y,p),Subs(x,y,q))
	|Subs(x,y,OR(p,q)) = OR(Subs(x,y,p),Subs(x,y,q))
	|Subs(x,y,IMPLY(p,q)) = IMPLY(Subs(x,y,p),Subs(x,y,q))
	|Subs(x,y,DOUBLEIMPLY(p,q)) = DOUBLEIMPLY(Subs(x,y,p),Subs(x,y,q))
	|Subs(x,y,FORALL(a,b)) = FORALL(a,Subs(x,y,b))
	|Subs(x,y,EXISTS(a,b)) = EXISTS(a,Subs(x,y,b))
	|Subs(x,y,NOT(p)) = NOT(Subs(x,y,p))
and SubsList(x,y,[]) = []
	|SubsList(x,y,p::ps) = Subs(x,y,p)::SubsList(x,y,ps)
;

fun SubstituteVarForConstant(a,b,val1) = Subs(a,Constant(Int.toString(val1)),b);

val prevconst = ref 0;

fun MakeTableaux(Variable(x))= [[Variable(x)]]
	|MakeTableaux(Constant(x)) = [[Constant(x)]]
	|MakeTableaux(FUNCTION(x,ls)) = [[FUNCTION(x,ls)]]
	|MakeTableaux(AND(x,y)) = JoinAll(MakeTableaux(x),MakeTableaux(y))
	|MakeTableaux(OR(x,y)) = List.concat[MakeTableaux(x),MakeTableaux(y)]
	|MakeTableaux(IMPLY(x,y)) = List.concat[MakeTableaux(NOT(x)),MakeTableaux(y)]
	|MakeTableaux(DOUBLEIMPLY(x,y)) = List.concat[MakeTableaux(AND(x,y)),MakeTableaux(AND(NOT(x),NOT(y)))]
	|MakeTableaux(FORALL(x,p)) = MakeTableaux(p)
	|MakeTableaux(EXISTS(x,p)) = 
		let
			val substituted = SubstituteVarForConstant(x,p,!prevconst)
		in
			(prevconst := !prevconst+1; MakeTableaux(substituted))
		end
	|MakeTableaux(NOT(NOT(x))) = MakeTableaux(x)
	|MakeTableaux(NOT(Variable(x))) = [[NOT(Variable(x))]]
	|MakeTableaux(NOT(Constant(x))) = [[NOT(Constant(x))]]
	|MakeTableaux(NOT(FUNCTION(x,ls))) = [[NOT(FUNCTION(x,ls))]]
	|MakeTableaux(NOT(AND(x,y))) = List.concat[MakeTableaux(NOT(x)),MakeTableaux(NOT(y))]
	|MakeTableaux(NOT(OR(x,y))) = JoinAll(MakeTableaux(NOT(x)),MakeTableaux(NOT(y)))
	|MakeTableaux(NOT(IMPLY(x,y))) = JoinAll(MakeTableaux(x),MakeTableaux(NOT(y)))
	|MakeTableaux(NOT(DOUBLEIMPLY(x,y))) = List.concat[MakeTableaux(AND(x,NOT(y))),MakeTableaux(AND(NOT(x),y))]
	|MakeTableaux(NOT(FORALL(x,p))) = 
		let
			val substituted = SubstituteVarForConstant(x,p,!prevconst)
		in
			(prevconst := !prevconst+1; MakeTableaux(NOT(substituted)))
		end
	|MakeTableaux(NOT(EXISTS(x,p))) = MakeTableaux(NOT(p))
;

fun CheckAllClosed([])= true
	|CheckAllClosed(x::xs)= CheckComp(x) andalso CheckAllClosed(xs)
;

(*val p:BoolExpr = Calc.parse_string("E(p,p*q) ;");*)
val p1:BoolExpr = Calc.parse_string(" (E(x,f[x]))->(E(y,f[y])) ;"); 
    (*f[p,q[r]] ;");*)

(*val q:BoolExpr=Calc.parse_string("((p*q) + ((~p)*r)) -> (((~p)+q)*(p+r)) ;");*)
val TableauxCreated = MakeTableaux(NOT(p1))
val result = CheckAllClosed(TableauxCreated)