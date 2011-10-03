/*exo1.l */
%{

%}

/*def*/

deb  \\begin
tabular tabular
/*table [table]
  opt_table [h|t|p|b]*/
opt_tableau [lcrp]
fusion \\multicolumn
trait_hor \\hline
separ_col &
fin_ligne \\\\
separ |
fin


accol_G {
accol_D }

word [^ \t\n]+
eol \n


/*
lettre[a-zA-Z]
aaa [a-zA-Z0-9_]
 */

/*rules analyseur lexico*/
%%
{word}  {wordCount++; charCount+=yyleng;}
{eol}   {charCount++; lineCount++;}
.       {charCount++;}
/*
{a}{n}{d} {return AND}
{lettre}{aaa}* {yyval chaine = (char *)strdup(yylead);return IDENTIFIANT;}
 */
%%
	/*subroutine*/
main(int argc, char** argv)
{
  if( argc>1)
    {
      FILE* ptr_file;
      if((ptr_file = fopen(argv[1], "r")) == NULL)
	{printf("blah"); exit(1);}
      yyin = ptr_file;
      yylex();
      printf("lineCount = %d, wordCount = %d\n, charCount = %d\n", lineCount, wordCount,charCount);
    }
}
