/************************************************************************/
/*! \file file_catalog.C
	RGlite test macro - File Catolog operations */ /*

         version number:    $LastChangedRevision$
         created by:        Anar Manafov
                            2006-11-15
         last changed by:   $LastChangedBy$ $LastChangedDate$

         Copyright (c) 2006 GSI GridTeam. All rights reserved.
*************************************************************************/
//
// Example of usage:
// root [1] .x tests/file_catalog.C
//


// STD
#include <iostream>


// helper function
void list_dir( Bool_t _NeedAll )
{
	TGridResult * result = gGrid->Ls();
	if( _NeedAll )
	{
		result->Print( "all" );
		delete result;
		return;
	}

	Int_t i = 0;
	while ( result->GetFileName( i ) )
	{
		cout << "File: " << result->GetFileName( i++ ) << endl;
	}
	delete result;
}

void NextPhase( Bool_t _NeedPause, const std::string &_strDescr, size_t _nPhaseNum )
{
	if( _NeedPause )
	{
		cout << "Press \"Enter\" to continue..." << endl;
		getchar();
	}
	cout << endl;
	cout << "<<<<[Phase #" << _nPhaseNum << "]>>>> " << _strDescr << endl;
}

int file_catalog()
{
	Bool_t bNeedPause = kFALSE;
	size_t count = 0;

	cout << "This is a test Macro for RGlite File Catalog operations" << endl;

	const char * const pszErrorString( "Test: FAILED" );
	const char * const pszOKString( "Test: OK" );

	NextPhase( bNeedPause, "Init of gLite API Wrapper", ++count );
	TGrid::Connect( "glite" );

	if ( gGrid )
	{
		string dir( "/grid" );
		NextPhase( bNeedPause, "Changing current working dir to " + dir, ++count );
		if ( !gGrid->Cd( dir.c_str() ) )
		{
			cout << pszErrorString << endl;
			return 1;
		}

		NextPhase( bNeedPause, "Asking for a PWD", ++count );
		cout << "Working Directory is " << gGrid->Pwd() << endl;

		NextPhase( bNeedPause, "Listing current dir", ++count );
		list_dir( kFALSE );

		dir = "/grid/dech";
		NextPhase( bNeedPause, "Changing current working dir to " + dir, ++count );
		if ( !gGrid->Cd( dir.c_str() ) )
		{
			cout << pszErrorString << endl;
			return 1;
		}

		NextPhase( bNeedPause, "Listing current dir", ++count );
		list_dir( kFALSE );

		const string newfile( "root_file_test10.file" );
		const TUUID uuid;
		const string strGUID( uuid.AsString() );
		const string strURL( "lfn://grid0.gsi.de/test/test3/" + newfile );
		const string strServer( "grid0.gsi.de" );


		NextPhase( bNeedPause, "Creating the file: "+ newfile, ++count );
		if ( !gGrid->Register( newfile.c_str(), strURL.c_str(), 0, strServer.c_str(), strGUID.c_str() ) )
		{
			cout << pszErrorString << endl;
			return 1;
		}

		NextPhase( bNeedPause, "Listing current dir", ++count );
		list_dir( kFALSE );

		NextPhase( bNeedPause, "Removing file: " + newfile, ++count );
		if ( !gGrid->Rm( newfile.c_str() ) )
		{
			cout << pszErrorString << endl;
			return 1;
		}

		NextPhase( bNeedPause, "Listing current dir", ++count );
		list_dir( kFALSE );

		NextPhase( bNeedPause, "Checking whether we can reconnection to LFC after a timeout", ++count );
		cout << "sleeping for a 1 min..." << endl;
		gSystem->Sleep( 60000 );
		cout << "waking up and continuing tests..." << endl;

		NextPhase( bNeedPause, "Listing current dir with 'all' details", ++count );
		list_dir( kTRUE );

		cout << "---------------------------" << endl;
		cout << pszOKString << endl;
		cout << "---------------------------" << endl;
		return 0;
	}
	else
	{
		cout << pszErrorString << endl;
		return 1;
	}
}
