%{
#include "highlight.parser.common.h"
#include "highlight.parser.h"

#include <string.h>

void _h_newstring( const char* c, yyscan_t scanner );

%}

character	[a-z]
legalchar	[a-z0-9_]
word		[0-9a-z'�������������������������������������������������������������]
allemuligetegn	[!"#$%'()*+,\-./0123456789:;=?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~����������������������������������������������������������������������������������������������]
  /* Tok vekk '&': */
url		[0-9a-z-\.:/\\?=]
blank		[ \t\n]
L		[A-Za-z0-9_'���������������������������������������������������������������]
letter		[A-Za-z0-9��������������������������������������������������������������]
wordletter	[A-Za-z0-9_]
apostroff	['`�"]
lettercaps	[A-Z�������������������������������]
ikkeletter	[!"#$%()*+,-./:;=?@[\]^{|}~���������������������������������]
letteresc	(AElig|Aacute|Acirc|Agrave|Aring|Atilde|Auml|Ccedil|ETH|Eacute|Ecirc|Egrave|Euml|Iacute|Icirc|Igrave|Iuml|Ntilde|Oacute|Ocirc|Ograve|Oslash|Otilde|Ouml|THORN|Uacute|Ucirc|Ugrave|Uuml|Yacute|aacute|acirc|aelig|agrave|aring|atilde|auml|ccedil|eacute|ecirc|egrave|eth|euml|iacute|icirc|igrave|iuml|ntilde|oacute|ocirc|ograve|oslash|otilde|ouml|szlig|thorn|uacute|ucirc|ugrave|uuml|yacute|yuml)
letternumesc	(#192|#193|#194|#195|#196|#197|#198|#199|#200|#201|#202|#203|#204|#205|#206|#207|#208|#209|#210|#211|#212|#213|#214|#216|#217|#218|#219|#220|#221|#222|#223|#224|#225|#226|#227|#228|#229|#230|#231|#232|#233|#234|#235|#236|#237|#238|#239|#240|#241|#242|#243|#244|#245|#246|#248|#249|#250|#251|#252|#253|#254|#255)
%option	nomain noyywrap reentrant
%%
\<div\>			{ return DIV_START; }
\<\/div\>		{ return DIV_END; }
\<span\>		{ return SPAN_START; }
\<\/span\>		{ return SPAN_END; }
\<h2\>			{ return HEAD_START; }
\<\/h2\>		{ return HEAD_END; }
({wordletter}|\&{letteresc};|\&{letternumesc};)({wordletter}|\&{letteresc};|\&{letternumesc};)+ { _h_newstring(yytext, yyscanner); return WORD; }	// Word
\&#[0-9][0-9][0-9];	{ _h_newstring(yytext, yyscanner); return OTHER; }	// Escape (not letter)
    /* \&{letternumesc};	{ _h_newstring(yytext, yyscanner); return OTHER; }	// Numeric escape */
    /* \&{letteresc};		{ _h_newstring(yytext, yyscanner); printf("%s\n", yytext); return OTHER; }	// Escape */
    /* [A-Za-z]+:\/\/{url}*	{ _h_newstring(yytext, yyscanner); return OTHER; }	// URL */
    /* {legalchar}+(\.{legalchar}+)*@{legalchar}+(\.{legalchar}+)*  { _h_newstring(yytext, yyscanner); return OTHER; }	// Epostadresse */
    /* {letter}*(\.{letter}+)+	{ _h_newstring(yytext, yyscanner); return OTHER; }	// Forkortelse eller URI */
[\.!?:;,]+		{ _h_newstring(yytext, yyscanner); return EOS; }	// End-Of-Sentence
[\ \t\n\r]+		{ (yyget_extra(yyscanner))->token.space = 1; }
<*>.			{ _h_newstring(yytext, yyscanner); return OTHER; }	// Andre tegn
%%

// Kopier teksten til 'token':
void _h_newstring( const char* c, yyscan_t scanner )
{
    struct _hp_yy_extra		*he = yyget_extra( scanner );

//Runar
// Bruker statisk minne, ikke dynamisk, da vi en skjelden gang f�r segfeil i free
// desuten er det raskere, ved at vi ikke gj�r systemkallet malloc heletiden

    he->stringtop++;
    if (he->stringtop>=128) he->stringtop = 0;

    #ifdef DEBUG
        //har fast lengde p� stringene. Hvis den er for lang vil ikke alt bli kopiert over. Usikker p� hva
        //det kan f�re til
	// Ax: Strenger lengre enn 2k er uansett s�ppel som ikke b�r vises i sammendraget.
	// Ax: Tror ikke dette skal ha noen d�rlige ringvirkninger.
        if (strlen(c) > h_maxNewString) {
                printf("New string is too long, will be truncated. Length was %i\n",strlen(c));
        }
    #endif

    if (strlen(c) > h_maxNewString)
	{
	    strcpy( he->stringcircle[he->stringtop], "[...]" );
	}
    else
	{
	    strncpy( he->stringcircle[he->stringtop], c, h_maxNewString );
	    he->stringcircle[he->stringtop][strlen(c)] = '\0';
	}

    he->token.str = he->stringcircle[he->stringtop];
}
