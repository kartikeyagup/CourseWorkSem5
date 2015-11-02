signature PROP =
	sig
		datatype BoolExpr = NOT of BoolExpr
						| AND of BoolExpr*BoolExpr
						| OR of BoolExpr*BoolExpr
						| IMPLY of BoolExpr*BoolExpr
						| DOUBLEIMPLY of BoolExpr*BoolExpr
						| Variable of string
end

structure PropLogic :> PROP = 
	struct
		datatype BoolExpr = NOT of BoolExpr
						| AND of BoolExpr*BoolExpr
						| OR of BoolExpr*BoolExpr
						| IMPLY of BoolExpr*BoolExpr
						| DOUBLEIMPLY of BoolExpr*BoolExpr
						| Variable of string
end;