Control.Print.printDepth := 100;

exception InvalidInput;

CM.make "sources.cm";

open PropLogic;

fun CheckComplimentary(Variable(x),NOT(Variable(y))) = (x=y)
	|CheckComplimentary(NOT(Variable(x)),Variable(y)) = (x=y)
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

fun MakeTableaux(Variable(x))= [[Variable(x)]]
	|MakeTableaux(AND(x,y)) = JoinAll(MakeTableaux(x),MakeTableaux(y))
	|MakeTableaux(OR(x,y)) = List.concat[MakeTableaux(x),MakeTableaux(y)]
	|MakeTableaux(IMPLY(x,y)) = List.concat[MakeTableaux(NOT(x)),MakeTableaux(y)]
	|MakeTableaux(DOUBLEIMPLY(x,y)) = List.concat[MakeTableaux(AND(x,y)),MakeTableaux(AND(NOT(x),NOT(y)))]
	|MakeTableaux(NOT(NOT(x))) = MakeTableaux(x)
	|MakeTableaux(NOT(Variable(x))) = [[NOT(Variable(x))]]
	|MakeTableaux(NOT(AND(x,y))) = List.concat[MakeTableaux(NOT(x)),MakeTableaux(NOT(y))]
	|MakeTableaux(NOT(OR(x,y))) = JoinAll(MakeTableaux(NOT(x)),MakeTableaux(NOT(y)))
	|MakeTableaux(NOT(IMPLY(x,y))) = JoinAll(MakeTableaux(x),MakeTableaux(NOT(y)))
	|MakeTableaux(NOT(DOUBLEIMPLY(x,y))) = List.concat[MakeTableaux(AND(x,NOT(y))),MakeTableaux(AND(NOT(x),y))]
;

fun CheckAllClosed([])= true
	|CheckAllClosed(x::xs)= CheckComp(x) andalso CheckAllClosed(xs)
;

val q:BoolExpr=Calc.parse_string("((p*q) + ((~p)*r)) -> (((~p)+q)*(p+r)) ;");
val TableauxCreated = MakeTableaux(NOT(q))
val result = CheckAllClosed(TableauxCreated)