Control.Print.printDepth := 100;
open HashString;


CM.make "sources.cm";

signature BDD=
	sig
		datatype Node = Node_Root of bool
			| Node_Node of string*Node*Node

		val var : Node -> string
		val StringEquiv : Node -> string
		val StringEquivTuple : (Node*Node) -> string
		val HashingNode : Node -> word
		val HashingTuple : (Node*Node) -> word 
		val NodeEqual : (Node*Node) -> bool
		val NodeTupleEqual : (Node*Node)*(Node*Node) -> bool
		val HashingTriple : string*Node*Node -> word
		val CompareTriple : (string*Node*Node)*(string*Node*Node) -> bool
		val CheckRoot : Node -> bool
		val CheckNode : Node -> bool
		val GetBool : Node -> bool
		val GetLow : Node -> Node
		val GetHigh : Node -> Node
end

structure Bdd :> BDD=
	struct
		datatype Node = Node_Root of bool
			| Node_Node of string*Node*Node

		fun var(Node_Node(x,_,_)) = x
			|var(Node_Root(x)) = if x then "true" else "false"
		;

		fun StringEquiv(Node_Root(true)) = "true"
			|StringEquiv(Node_Root(false)) = "false"
			|StringEquiv(Node_Node(x,y,z)) = String.concat([StringEquiv(y),",",x,",",StringEquiv(z)])
		;

		fun StringEquivTuple(n1,n2) = String.concat([StringEquiv(n1),".",StringEquiv(n2)])
		;

		fun HashingNode(n1) = HashString.hashString(StringEquiv(n1));

		fun HashingTuple(n1,n2) = HashString.hashString(StringEquivTuple(n1,n2));

		fun NodeEqual(Node_Root(x),Node_Root(y))= (x=y)
			|NodeEqual(Node_Node(_,_,_),Node_Root(_))= false
			|NodeEqual(Node_Root(_),Node_Node(_,_,_))= false
			|NodeEqual(Node_Node(a,b,c),Node_Node(d,e,f)) = (a=d) andalso NodeEqual(b,e) andalso NodeEqual(c,f)
		;

		fun NodeTupleEqual((a,b),(c,d)) = NodeEqual(a,c) andalso NodeEqual(b,d);

		fun HashingTriple(a,b,c) = HashString.hashString(String.concat([a,".",StringEquiv(b),".",StringEquiv(c)]));

		fun CompareTriple((a,b,c),(d,e,f)) = (a=d) andalso NodeTupleEqual((b,c),(e,f));

		fun CheckRoot(Node_Root(x))= true
			|CheckRoot(Node_Node(_,_,_))=false
		;

		fun CheckNode(Node_Node(_,_,_))= true
			|CheckNode(Node_Root(_))= false
		;

		fun GetBool(Node_Root(x))= x;

		fun GetLow(Node_Node(a,b,c)) = b
			|GetLow(Node_Root(a)) = Node_Root(a)
		;
		
		fun GetHigh(Node_Node(a,b,c)) = c
			|GetHigh(Node_Root(a)) = Node_Root(a)
		;

end


open Bdd;

datatype T = T_Table of (Node,(string*Node*Node)) HashTable.hash_table;
datatype H = H_Table of ((string*Node*Node),Node) HashTable.hash_table;
datatype G = G_Table of ((Node*Node),Node) HashTable.hash_table;
datatype Complete = Complete of H*T*G*Node*Program.BoolExpr;

fun Mk(H_Table(h),T_Table(t),G,i:string,lo:Node,hi:Node): H*T*G*Node=
	if NodeEqual(lo,hi) then (H_Table(h),T_Table(t),G,lo)
	else if (HashTable.inDomain h (i,lo,hi)) then (H_Table(h),T_Table(t),G,(HashTable.lookup h (i,lo,hi)))
	else
		let
			val p1 ="in the else case\n";
			val n1 = Node_Node(i,lo,hi);
			val addedint = HashTable.insert t (n1,(i,lo,hi));
			val addedinh = HashTable.insert h ((i,lo,hi),n1) ;
		in
			(H_Table(h),T_Table(t),G,n1)
		end
;

fun App(H,T,G_Table(g),Program.AND,n1,n2)=
		if (HashTable.inDomain g (n1,n2)) then (HashTable.lookup g (n1,n2),H,T,G_Table(g))
		else if (CheckRoot(n1) andalso CheckRoot(n2)) then 
			let
				val u = GetBool(n1) andalso GetBool(n2);
				val p = HashTable.insert g ((n1,n2),Node_Root(u));
			in
				(Node_Root(u),H,T,G_Table(g))
			end 
		else if (CheckRoot(n1) andalso CheckNode(n2)) then
			if (GetBool(n1)) then 
				let
					val q = print "Bool value was true\n";
				in
					(n2,H,T,G_Table(g))		
				end
			else 
				let
					val r = "Bool value is false\n";
				in
					(n1,H,T,G_Table(g))
				end
		else if (CheckRoot(n2) andalso CheckNode(n1)) then
			if (GetBool(n2)) then 
				(n1,H,T,G_Table(g))		
			else 
				(n2,H,T,G_Table(g))
		else if (var(n1)=var(n2)) then
			let
				val (app1,app2,app3,app4) = App(H,T,G_Table(g),Program.AND,GetLow(n1),GetLow(n2))
				val (app5,app6,app7,app8) = App(app2,app3,app4,Program.AND,GetHigh(n1),GetHigh(n2))
				val (A,B,G_Table(g1),D) = Mk(app6,app7,app8,var(n1),app1,app5)
				val addeding = HashTable.insert g1 ((n1,n2), D) 
			in
				(D,A,B,G_Table(g1))
			end
		else if (var(n1)<var(n2)) then
			let
				val d1 = print "in else if\n";
				val d1 = print "string for n1 ";
				val d1= print (StringEquiv(n1));
				val d1 =print "\n";
				val d1 = print "string for n2 ";
				val d1= print (StringEquiv(n2));
				val d1 =print "\n";
				val (app1,app2,app3,app4) = App(H,T,G_Table(g),Program.AND,GetLow(n1),n2)
				val d1 = print "string for app1 ";
				val d1= print (StringEquiv(app1));
				val d1 =print "\n";
				val (app5,app6,app7,app8) = App(app2,app3,app4,Program.AND,GetHigh(n1),n2)
				val d1 = print "string for app5 ";
				val d1= print (StringEquiv(app5));
				val d1 =print "\n";
				val (A,B,G_Table(g1),D) = Mk(app6,app7,app8,var(n1),app1,app5)
				val d1 = print "made\n";
				val addeding = HashTable.insert g1 ((n1,n2), D) 
			in
				(D,A,B,G_Table(g1))
			end
		else
			let
				val (app1,app2,app3,app4) = App(H,T,G_Table(g),Program.AND,(n1),GetLow(n2))
				val (app5,app6,app7,app8) = App(app2,app3,app4,Program.AND,(n1),GetHigh(n2))
				val (A,B,G_Table(g1),D) = Mk(app6,app7,app8,var(n2),app1,app5)
				val addeding = HashTable.insert g1 ((n1,n2), D) 
			in
				(D,A,B,G_Table(g1))
			end
	|App(H,T,G_Table(g),Program.OR,n1,n2)=
		if (HashTable.inDomain g (n1,n2)) then (HashTable.lookup g (n1,n2),H,T,G_Table(g))
		else if (CheckRoot(n1) andalso CheckRoot(n2)) then 
			let
				val u = GetBool(n1) orelse GetBool(n2);
				val p = HashTable.insert g ((n1,n2),Node_Root(u));
			in
				(Node_Root(u),H,T,G_Table(g))
			end 
		else if (CheckRoot(n1) andalso CheckNode(n2)) then
			if (GetBool(n1)) then 
				(n1,H,T,G_Table(g))		
			else 
				(n2,H,T,G_Table(g))
		else if (CheckRoot(n2) andalso CheckNode(n1)) then
			if (GetBool(n2)) then 
				(n2,H,T,G_Table(g))		
			else 
				(n1,H,T,G_Table(g))
		else if (var(n1)=var(n2)) then
			let
				val (app1,app2,app3,app4) = App(H,T,G_Table(g),Program.OR,GetLow(n1),GetLow(n2))
				val (app5,app6,app7,app8) = App(app2,app3,app4,Program.OR,GetHigh(n1),GetHigh(n2))
				val (A,B,G_Table(g1),D) = Mk(app6,app7,app8,var(n1),app1,app5)
				val addeding = HashTable.insert g1 ((n1,n2), D) 
			in
				(D,A,B,G_Table(g1))
			end
		else if (var(n1)<var(n2)) then
			let
				val (app1,app2,app3,app4) = App(H,T,G_Table(g),Program.OR,GetLow(n1),n2)
				val (app5,app6,app7,app8) = App(app2,app3,app4,Program.OR,GetHigh(n1),n2)
				val (A,B,G_Table(g1),D) = Mk(app6,app7,app8,var(n1),app1,app5)
				val addeding = HashTable.insert g1 ((n1,n2), D) 
			in
				(D,A,B,G_Table(g1))
			end
		else
			let
				val (app1,app2,app3,app4) = App(H,T,G_Table(g),Program.OR,(n1),GetLow(n2))
				val (app5,app6,app7,app8) = App(app2,app3,app4,Program.OR,(n1),GetHigh(n2))
				val (A,B,G_Table(g1),D) = Mk(app6,app7,app8,var(n2),app1,app5)
				val addeding = HashTable.insert g1 ((n1,n2), D) 
			in
				(D,A,B,G_Table(g1))
			end
	
;			


fun MakeBDD(H:H,T:T,G:G,Program.Constant(x):Program.BoolExpr): H*T*G*Node=(H,T,G,Node_Root(x))
	|MakeBDD(H,T,G,Program.Variable(x))=(H,T,G,Node_Node(x,Node_Root(false),Node_Root(true)))
	|MakeBDD(H,T,G,Program.OprBinary(l1,y,z))= 
		let
			val (app1,app2,app3,app4) = MakeBDD(H,T,G,y);
			val q = print "done for first\n";
			val (app5,app6,app7,app8) = MakeBDD(app1,app2,app3,z);
			val q = print "done for second\n";
			val (app9,app10,app11,app12) = App(app5,app6,app7,l1,app4,app8)
		in
			(app10,app11,app12,app9)
		end
	|MakeBDD(H,T,G,Program.OprUnary(x,Program.Variable(y)))= 
		(H,T,G,Node_Node(y,Node_Root(true),Node_Root(false)))
;

fun initT() =
	let
		val Tht : (Node, (string*Node*Node)) HashTable.hash_table = HashTable.mkTable(HashingNode, NodeEqual)(17, Domain);
	in
		T_Table(Tht)
	end
;

fun initH() =
	let
		val Hht : ((string*Node*Node),Node) HashTable.hash_table = HashTable.mkTable(HashingTriple, CompareTriple)(17, Domain);
	in
		H_Table(Hht)
	end
;

fun initG() =
	let
		val Ght : ((Node*Node),Node) HashTable.hash_table = HashTable.mkTable(HashingTuple, NodeTupleEqual)(17, Domain);
	in
		G_Table(Ght)
	end
;

fun GenerateString(Node_Root(x)) = ""
	|GenerateString(Node_Node(a,b,c)) = concat[concat([a," -> ", var(b)]),";",  concat([a, " -> ", var(c)]) , ";",GenerateString(b),GenerateString(c)]
;

fun MakeTotalString(l)= concat["digraph G { ", GenerateString(l) , "}"];

fun GetNode(_,_,_,x)=x;

(*val q:Program.BoolExpr=Calc.parse_string("(x2*x1);");*)
val q:Program.BoolExpr=Calc.parse_string("x1*(x2*(x1+x3));");

val writestream = TextIO.openOut "test.dot";
(*TextIO.output(writestream, "This is a message to write to your stream.");*)



val res =GetNode(MakeBDD(initH(),initT(),initG(),q));

val strout= MakeTotalString(res);

TextIO.output(writestream,strout);

TextIO.closeOut(writestream);
(*val ht : (string, int) HashTable.hash_table = HashTable.mkTable(HashString.hashString, op=)(17, Domain);*)

(*val ht : (Node, (string*Node*Node)) HashTable.hash_table = HashTable.mkTable(HashingNode, NodeEqual)(17, Domain);*)

