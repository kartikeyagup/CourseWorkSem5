signature PROGRAM =
	sig
		datatype BoolExpr = OprUnary of BoolOpr*BoolExpr
						| OprBinary of BoolOpr*BoolExpr*BoolExpr
						| OprTernary of BoolOpr*BoolExpr*BoolExpr*BoolExpr
						| Variable of string
						| Constant of bool

		and BoolOpr = AND
				| OR
				| NOT
				| IMPLY
				| DOUBLEIMPLY
				| IFTHENELSE
end

structure Program :> PROGRAM = 
	struct
		datatype BoolExpr = OprUnary of BoolOpr*BoolExpr
						| OprBinary of BoolOpr*BoolExpr*BoolExpr
						| OprTernary of BoolOpr*BoolExpr*BoolExpr*BoolExpr
						| Variable of string
						| Constant of bool

		and BoolOpr = AND
				| OR
				| NOT
				| IMPLY
				| DOUBLEIMPLY
				| IFTHENELSE
end;