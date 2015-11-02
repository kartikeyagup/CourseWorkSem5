structure Tokens = Tokens

type pos = int
type svalue = Tokens.svalue
type ('a,'b) token = ('a,'b) Tokens.token
type lexresult= (svalue,pos) token

val pos = ref 0
fun eof () = Tokens.EOF(!pos,!pos)
fun error (e,l,_) = TextIO.output (TextIO.stdOut, String.concat[
	"line ", (Int.toString l), ": ", e, "\n"])

%%
%header (functor CalcLexFun(structure Tokens: Calc_TOKENS));
alpha=[A-Za-z];
alphanum=[A-Za-z0-9];
caps=[A-Z];
sm=[a-z];
digit=[0-9];
ws = [\ \t];
%%
\n       => (pos := (!pos) + 1; lex());
{ws}+    => (lex());
"+"		 => (Tokens.OR(!pos,!pos));
"->"	 => (Tokens.IMPLY(!pos,!pos));
"="		 => (Tokens.DOUBLEIMPLY(!pos,!pos));
"\*"	 => (Tokens.AND(!pos,!pos));
"V"		 => (Tokens.FORALL(!pos,!pos));
"E"		 => (Tokens.EXISTS(!pos,!pos));
"\~" 	 => (Tokens.NOT(!pos,!pos));
")"		 => (Tokens.RPAREN(!pos,!pos));
"("		 => (Tokens.LPAREN(!pos,!pos));
"["		 => (Tokens.BOXLPAREN(!pos,!pos));
"]"		 => (Tokens.BOXRPAREN(!pos,!pos));
";"		 => (Tokens.SEMI(!pos,!pos));
","		 => (Tokens.COMMA(!pos,!pos));
"\."	 => (Tokens.DOT(!pos,!pos));
{alphanum}+ => (Tokens.VAR(yytext,!pos,!pos));
"."      => (error ("ignoring bad character "^yytext,!pos,!pos); lex());