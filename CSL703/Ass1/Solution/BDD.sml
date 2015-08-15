signature BDD=
	sig
		datatype Node = Node_Root of bool
			| Node_Node of string*Node*Node
			
