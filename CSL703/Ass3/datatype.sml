signature PRED =
	sig
		datatype BoolExpr = NOT of BoolExpr
						| AND of BoolExpr*BoolExpr
						| OR of BoolExpr*BoolExpr
						| IMPLY of BoolExpr*BoolExpr
						| DOUBLEIMPLY of BoolExpr*BoolExpr
						| Variable of string
						| Constant of string
						| FUNCTION of string*(BoolExpr list)
						| FORALL of string*BoolExpr
						| EXISTS of string*BoolExpr
end

structure PredLogic :> PRED = 
	struct
		datatype BoolExpr = NOT of BoolExpr
						| AND of BoolExpr*BoolExpr
						| OR of BoolExpr*BoolExpr
						| IMPLY of BoolExpr*BoolExpr
						| DOUBLEIMPLY of BoolExpr*BoolExpr
						| Variable of string
						| Constant of string
						| FUNCTION of string*(BoolExpr list)
						| FORALL of string*BoolExpr
						| EXISTS of string*BoolExpr
end;