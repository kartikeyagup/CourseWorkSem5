functor CalcLrValsFun(structure Token : TOKEN)
 : sig structure ParserData : PARSER_DATA
       structure Tokens : Calc_TOKENS
   end
 = 
struct
structure ParserData=
struct
structure Header = 
struct

end
structure LrTable = Token.LrTable
structure Token = Token
local open LrTable in 
val table=let val actionRows =
"\
\\001\000\001\000\008\000\002\000\007\000\003\000\006\000\005\000\005\000\
\\010\000\004\000\000\000\
\\001\000\006\000\021\000\008\000\013\000\009\000\012\000\011\000\011\000\
\\012\000\010\000\013\000\009\000\000\000\
\\001\000\007\000\000\000\014\000\000\000\000\000\
\\001\000\008\000\013\000\009\000\012\000\011\000\011\000\012\000\010\000\
\\013\000\009\000\015\000\022\000\000\000\
\\025\000\008\000\013\000\009\000\012\000\011\000\011\000\012\000\010\000\
\\013\000\009\000\000\000\
\\026\000\008\000\013\000\009\000\012\000\011\000\011\000\012\000\010\000\
\\013\000\009\000\000\000\
\\027\000\008\000\013\000\009\000\012\000\011\000\011\000\012\000\010\000\
\\013\000\009\000\000\000\
\\028\000\008\000\013\000\009\000\012\000\011\000\011\000\012\000\010\000\
\\013\000\009\000\000\000\
\\029\000\008\000\013\000\009\000\012\000\011\000\011\000\012\000\010\000\
\\013\000\009\000\000\000\
\\030\000\008\000\013\000\009\000\012\000\011\000\011\000\012\000\010\000\
\\013\000\009\000\000\000\
\\031\000\008\000\013\000\009\000\012\000\011\000\011\000\012\000\010\000\
\\013\000\009\000\000\000\
\\032\000\000\000\
\\033\000\000\000\
\\034\000\000\000\
\\035\000\000\000\
\"
val actionRowNumbers =
"\000\000\004\000\000\000\000\000\
\\013\000\012\000\011\000\000\000\
\\000\000\000\000\000\000\000\000\
\\007\000\001\000\003\000\009\000\
\\008\000\005\000\006\000\014\000\
\\000\000\010\000\002\000"
val gotoT =
"\
\\001\000\022\000\002\000\001\000\000\000\
\\000\000\
\\002\000\012\000\000\000\
\\002\000\013\000\000\000\
\\000\000\
\\000\000\
\\000\000\
\\002\000\014\000\000\000\
\\002\000\015\000\000\000\
\\002\000\016\000\000\000\
\\002\000\017\000\000\000\
\\002\000\018\000\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\000\000\
\\002\000\021\000\000\000\
\\000\000\
\\000\000\
\"
val numstates = 23
val numrules = 11
val s = ref "" and index = ref 0
val string_to_int = fn () => 
let val i = !index
in index := i+2; Char.ord(String.sub(!s,i)) + Char.ord(String.sub(!s,i+1)) * 256
end
val string_to_list = fn s' =>
    let val len = String.size s'
        fun f () =
           if !index < len then string_to_int() :: f()
           else nil
   in index := 0; s := s'; f ()
   end
val string_to_pairlist = fn (conv_key,conv_entry) =>
     let fun f () =
         case string_to_int()
         of 0 => EMPTY
          | n => PAIR(conv_key (n-1),conv_entry (string_to_int()),f())
     in f
     end
val string_to_pairlist_default = fn (conv_key,conv_entry) =>
    let val conv_row = string_to_pairlist(conv_key,conv_entry)
    in fn () =>
       let val default = conv_entry(string_to_int())
           val row = conv_row()
       in (row,default)
       end
   end
val string_to_table = fn (convert_row,s') =>
    let val len = String.size s'
        fun f ()=
           if !index < len then convert_row() :: f()
           else nil
     in (s := s'; index := 0; f ())
     end
local
  val memo = Array.array(numstates+numrules,ERROR)
  val _ =let fun g i=(Array.update(memo,i,REDUCE(i-numstates)); g(i+1))
       fun f i =
            if i=numstates then g i
            else (Array.update(memo,i,SHIFT (STATE i)); f (i+1))
          in f 0 handle General.Subscript => ()
          end
in
val entry_to_action = fn 0 => ACCEPT | 1 => ERROR | j => Array.sub(memo,(j-2))
end
val gotoT=Array.fromList(string_to_table(string_to_pairlist(NT,STATE),gotoT))
val actionRows=string_to_table(string_to_pairlist_default(T,entry_to_action),actionRows)
val actionRowNumbers = string_to_list actionRowNumbers
val actionT = let val actionRowLookUp=
let val a=Array.fromList(actionRows) in fn i=>Array.sub(a,i) end
in Array.fromList(List.map actionRowLookUp actionRowNumbers)
end
in LrTable.mkLrTable {actions=actionT,gotos=gotoT,numRules=numrules,
numStates=numstates,initialState=STATE 0}
end
end
local open Header in
type pos = int
type arg = unit
structure MlyValue = 
struct
datatype svalue = VOID | ntVOID of unit ->  unit
 | VAR of unit ->  (string) | TERM of unit ->  (Program.BoolExpr)
 | PROG of unit ->  (Program.BoolExpr)
end
type svalue = MlyValue.svalue
type result = Program.BoolExpr
end
structure EC=
struct
open LrTable
infix 5 $$
fun x $$ y = y::x
val is_keyword =
fn _ => false
val preferred_change : (term list * term list) list = 
nil
val noShift = 
fn (T 6) => true | _ => false
val showTerminal =
fn (T 0) => "VAR"
  | (T 1) => "TRUE"
  | (T 2) => "FALSE"
  | (T 3) => "DOT"
  | (T 4) => "LPAREN"
  | (T 5) => "RPAREN"
  | (T 6) => "EOF"
  | (T 7) => "OR"
  | (T 8) => "AND"
  | (T 9) => "NOT"
  | (T 10) => "IMPLY"
  | (T 11) => "EQUAL"
  | (T 12) => "IF"
  | (T 13) => "SEMI"
  | (T 14) => "COMMA"
  | _ => "bogus-term"
local open Header in
val errtermvalue=
fn _ => MlyValue.VOID
end
val terms : term list = nil
 $$ (T 14) $$ (T 13) $$ (T 12) $$ (T 11) $$ (T 10) $$ (T 9) $$ (T 8)
 $$ (T 7) $$ (T 6) $$ (T 5) $$ (T 4) $$ (T 3) $$ (T 2) $$ (T 1)end
structure Actions =
struct 
exception mlyAction of int
local open Header in
val actions = 
fn (i392,defaultPos,stack,
    (()):arg) =>
case (i392,stack)
of  ( 0, ( ( _, ( MlyValue.TERM TERM1, TERM1left, TERM1right)) :: 
rest671)) => let val  result = MlyValue.PROG (fn _ => let val  (TERM
 as TERM1) = TERM1 ()
 in (TERM)
end)
 in ( LrTable.NT 0, ( result, TERM1left, TERM1right), rest671)
end
|  ( 1, ( ( _, ( MlyValue.TERM TERM2, _, TERM2right)) :: _ :: ( _, ( 
MlyValue.TERM TERM1, TERM1left, _)) :: rest671)) => let val  result = 
MlyValue.TERM (fn _ => let val  TERM1 = TERM1 ()
 val  TERM2 = TERM2 ()
 in (Program.OprBinary(Program.AND,TERM1,TERM2))
end)
 in ( LrTable.NT 1, ( result, TERM1left, TERM2right), rest671)
end
|  ( 2, ( ( _, ( MlyValue.TERM TERM2, _, TERM2right)) :: _ :: ( _, ( 
MlyValue.TERM TERM1, TERM1left, _)) :: rest671)) => let val  result = 
MlyValue.TERM (fn _ => let val  TERM1 = TERM1 ()
 val  TERM2 = TERM2 ()
 in (Program.OprBinary(Program.OR,TERM1, TERM2))
end)
 in ( LrTable.NT 1, ( result, TERM1left, TERM2right), rest671)
end
|  ( 3, ( ( _, ( MlyValue.TERM TERM1, _, TERM1right)) :: ( _, ( _, 
NOT1left, _)) :: rest671)) => let val  result = MlyValue.TERM (fn _ =>
 let val  (TERM as TERM1) = TERM1 ()
 in (Program.OprUnary(Program.NOT, TERM))
end)
 in ( LrTable.NT 1, ( result, NOT1left, TERM1right), rest671)
end
|  ( 4, ( ( _, ( MlyValue.TERM TERM2, _, TERM2right)) :: _ :: ( _, ( 
MlyValue.TERM TERM1, TERM1left, _)) :: rest671)) => let val  result = 
MlyValue.TERM (fn _ => let val  TERM1 = TERM1 ()
 val  TERM2 = TERM2 ()
 in (Program.OprBinary(Program.IMPLY, TERM1,TERM2))
end)
 in ( LrTable.NT 1, ( result, TERM1left, TERM2right), rest671)
end
|  ( 5, ( ( _, ( MlyValue.TERM TERM2, _, TERM2right)) :: _ :: ( _, ( 
MlyValue.TERM TERM1, TERM1left, _)) :: rest671)) => let val  result = 
MlyValue.TERM (fn _ => let val  TERM1 = TERM1 ()
 val  TERM2 = TERM2 ()
 in (Program.OprBinary(Program.DOUBLEIMPLY, TERM1,TERM2))
end)
 in ( LrTable.NT 1, ( result, TERM1left, TERM2right), rest671)
end
|  ( 6, ( ( _, ( MlyValue.TERM TERM3, _, TERM3right)) :: _ :: ( _, ( 
MlyValue.TERM TERM2, _, _)) :: _ :: ( _, ( MlyValue.TERM TERM1, 
TERM1left, _)) :: rest671)) => let val  result = MlyValue.TERM (fn _
 => let val  TERM1 = TERM1 ()
 val  TERM2 = TERM2 ()
 val  TERM3 = TERM3 ()
 in (Program.OprTernary(Program.IFTHENELSE,TERM1,TERM2,TERM3))
end)
 in ( LrTable.NT 1, ( result, TERM1left, TERM3right), rest671)
end
|  ( 7, ( ( _, ( MlyValue.VAR VAR1, VAR1left, VAR1right)) :: rest671))
 => let val  result = MlyValue.TERM (fn _ => let val  (VAR as VAR1) = 
VAR1 ()
 in (Program.Variable VAR)
end)
 in ( LrTable.NT 1, ( result, VAR1left, VAR1right), rest671)
end
|  ( 8, ( ( _, ( _, TRUE1left, TRUE1right)) :: rest671)) => let val  
result = MlyValue.TERM (fn _ => (Program.Constant true))
 in ( LrTable.NT 1, ( result, TRUE1left, TRUE1right), rest671)
end
|  ( 9, ( ( _, ( _, FALSE1left, FALSE1right)) :: rest671)) => let val 
 result = MlyValue.TERM (fn _ => (Program.Constant false))
 in ( LrTable.NT 1, ( result, FALSE1left, FALSE1right), rest671)
end
|  ( 10, ( ( _, ( _, _, RPAREN1right)) :: ( _, ( MlyValue.TERM TERM1,
 _, _)) :: ( _, ( _, LPAREN1left, _)) :: rest671)) => let val  result
 = MlyValue.TERM (fn _ => let val  (TERM as TERM1) = TERM1 ()
 in (TERM)
end)
 in ( LrTable.NT 1, ( result, LPAREN1left, RPAREN1right), rest671)
end
| _ => raise (mlyAction i392)
end
val void = MlyValue.VOID
val extract = fn a => (fn MlyValue.PROG x => x
| _ => let exception ParseInternal
	in raise ParseInternal end) a ()
end
end
structure Tokens : Calc_TOKENS =
struct
type svalue = ParserData.svalue
type ('a,'b) token = ('a,'b) Token.token
fun VAR (i,p1,p2) = Token.TOKEN (ParserData.LrTable.T 0,(
ParserData.MlyValue.VAR (fn () => i),p1,p2))
fun TRUE (p1,p2) = Token.TOKEN (ParserData.LrTable.T 1,(
ParserData.MlyValue.VOID,p1,p2))
fun FALSE (p1,p2) = Token.TOKEN (ParserData.LrTable.T 2,(
ParserData.MlyValue.VOID,p1,p2))
fun DOT (p1,p2) = Token.TOKEN (ParserData.LrTable.T 3,(
ParserData.MlyValue.VOID,p1,p2))
fun LPAREN (p1,p2) = Token.TOKEN (ParserData.LrTable.T 4,(
ParserData.MlyValue.VOID,p1,p2))
fun RPAREN (p1,p2) = Token.TOKEN (ParserData.LrTable.T 5,(
ParserData.MlyValue.VOID,p1,p2))
fun EOF (p1,p2) = Token.TOKEN (ParserData.LrTable.T 6,(
ParserData.MlyValue.VOID,p1,p2))
fun OR (p1,p2) = Token.TOKEN (ParserData.LrTable.T 7,(
ParserData.MlyValue.VOID,p1,p2))
fun AND (p1,p2) = Token.TOKEN (ParserData.LrTable.T 8,(
ParserData.MlyValue.VOID,p1,p2))
fun NOT (p1,p2) = Token.TOKEN (ParserData.LrTable.T 9,(
ParserData.MlyValue.VOID,p1,p2))
fun IMPLY (p1,p2) = Token.TOKEN (ParserData.LrTable.T 10,(
ParserData.MlyValue.VOID,p1,p2))
fun EQUAL (p1,p2) = Token.TOKEN (ParserData.LrTable.T 11,(
ParserData.MlyValue.VOID,p1,p2))
fun IF (p1,p2) = Token.TOKEN (ParserData.LrTable.T 12,(
ParserData.MlyValue.VOID,p1,p2))
fun SEMI (p1,p2) = Token.TOKEN (ParserData.LrTable.T 13,(
ParserData.MlyValue.VOID,p1,p2))
fun COMMA (p1,p2) = Token.TOKEN (ParserData.LrTable.T 14,(
ParserData.MlyValue.VOID,p1,p2))
end
end
