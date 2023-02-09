#include <dbmParser.h>
#include <dbmErrorStack.h>
#include <dbmUtils.h>



main()
{
    dbmParserContext    * sCtx;
    dbmErrorStack         sErrStack;
    int                   sRet;
    
    sCtx = (dbmParserContext *)malloc( sizeof(dbmParserContext) );

    sRet = dbmInitParserContext( sCtx, &sErrStack );
    if( sRet != 0 )
    {
        printf( "failed to init a context for parser\n" );
        exit(-1);
    }
   
    sRet = dbmParseText( sCtx,
                         "select 1 from dual",
                         &sErrStack );

    if( sRet != 0 )
    {
        printf( "failed to parse a context for parser\n" );
        exit(-1);
    }

    dbmFinalizeParserContext( sCtx );
    
}
