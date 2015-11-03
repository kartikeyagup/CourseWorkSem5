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

val variablelast = ref 0;

fun RenameVariable(x,y,Variable(p))=if (p=x) then Variable(y) else Variable(p)
	|RenameVariable(x,y,Constant(p))=Constant(p)
	|RenameVariable(x,y,AND(a,b))=AND(RenameVariable(x,y,a),RenameVariable(x,y,b))
	|RenameVariable(x,y,OR(a,b)) =OR(RenameVariable(x,y,a),RenameVariable(x,y,b))
	|RenameVariable(x,y,IMPLY(a,b))=IMPLY(RenameVariable(x,y,a),RenameVariable(x,y,b))
	|RenameVariable(x,y,DOUBLEIMPLY(a,b))=DOUBLEIMPLY(RenameVariable(x,y,a),RenameVariable(x,y,b))
	|RenameVariable(x,y,FUNCTION(l,ls))=FUNCTION(l,RenameVariableList(x,y,ls))
	|RenameVariable(x,y,FORALL(a,b))= if (x=a) then FORALL(y,RenameVariable(x,y,b)) else FORALL(a,RenameVariable(x,y,b))
	|RenameVariable(x,y,EXISTS(a,b))= if (x=a) then EXISTS(y,RenameVariable(x,y,b)) else EXISTS(a,RenameVariable(x,y,b))
	|RenameVariable(x,y,NOT(p))=NOT(RenameVariable(x,y,p))
and RenameVariableList(x,y,[])=[]
	|RenameVariableList(x,y,p::ps)=RenameVariable(x,y,p)::RenameVariableList(x,y,ps)
;

fun RenameAll(Variable(x))=Variable(x)
	|RenameAll(Constant(x))=Constant(x)
	|RenameAll(FORALL(a,b))=
		let
			val FORALL(a1,a2) = RenameVariable(a,Int.toString(!variablelast),FORALL(a,b))
		in
			(variablelast := !variablelast+1 ; FORALL(a1,RenameAll(a2)))
		end
	|RenameAll(EXISTS(a,b))=
		let
			val EXISTS(a1,a2) = RenameVariable(a,Int.toString(!variablelast),EXISTS(a,b))
		in
			(variablelast := !variablelast+1 ; EXISTS(a1,RenameAll(a2)))
		end
	|RenameAll(AND(a,b))=AND(RenameAll(a),RenameAll(b))
	|RenameAll(OR(a,b))=OR(RenameAll(a),RenameAll(b))
	|RenameAll(IMPLY(a,b))=IMPLY(RenameAll(a),RenameAll(b))
	|RenameAll(DOUBLEIMPLY(a,b))=DOUBLEIMPLY(RenameAll(a),RenameAll(b))
	|RenameAll(NOT(a))=NOT(RenameAll(a))
	|RenameAll(FUNCTION(a,b))=FUNCTION(a,map RenameAll b)
;

fun CheckAllClosed([])= true
	|CheckAllClosed(x::xs)= CheckComp(x) andalso CheckAllClosed(xs)
;

(*val p:BoolExpr = Calc.parse_string("E(p,p*q) ;");*)
val p1:BoolExpr = Calc.parse_string(" (E(x,f[x]))->(E(x,f[x])) ;"); 
    (*f[p,q[r]] ;");*)

val renamed = RenameAll(p1);

(*val q:BoolExpr=Calc.parse_string("((p*q) + ((~p)*r)) -> (((~p)+q)*(p+r)) ;");*)
val TableauxCreated = MakeTableaux(NOT(renamed))
val result = CheckAllClosed(TableauxCreated)