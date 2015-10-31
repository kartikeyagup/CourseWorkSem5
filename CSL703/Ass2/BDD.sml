signature BDD=
	sig
		datatype Node = Node_Root of bool
			| Node_Node of string*Node*Node

		val var : Node -> string
		val StringEquiv : Node -> string
		val StringEquivTuple : (Node*Node) -> string
		val HashingTuple : (Node*Node) -> word 
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

		fun HashingTuple(n1,n2) = HashString.hashString("yoyo")
		;
end