/************************************************************************/
/*! \file job_submission.C
	RGlite test macro - Job submission *//*

         version number:    $LastChangedRevision$
         created by:        Anar Manafov
                            2006-11-13
         last changed by:   $LastChangedBy$ $LastChangedDate$

         Copyright (c) 2006 GSI GridTeam. All rights reserved.
*************************************************************************/
//
// Example of usage:
// root [1] .x tests/job_submission.C("/home/anar/jdl/test.jdl")
//

// STD
#include <iostream>
// RGlite
#include "TGridJobStatus.h"

using namespace std;

const size_t MAX_ITER_COUNT = 50;
const size_t SLEEP_TIME = 20000;// in milliseconds

Int_t job_submission( const char *_JDL )
{
  TGrid::Connect("glite");
  
  TGridJob *job = gGrid->Submit( _JDL );
  if( !job )
    {
      cerr << "TGridJob is NULL." << endl;
      return 1;
    }
  
  TGridJobStatus *status = job->GetJobStatus();
  if( !status )
    {
      cerr << "TGridJobStatus is NULL." << endl;
      return 1;
    }
  
  for( size_t i = 0; i < MAX_ITER_COUNT; ++i )
    {
      cout << " - - - - - - - - - - - - - " << endl;
      cout << "Iteration #" << i << endl;
      switch ( status->GetStatus() )
	{
	case TGridJobStatus::kDONE:
	  job->GetOutputSandbox("/tmp");
	  return 0;
	case TGridJobStatus::kABORTED:
	case TGridJobStatus::kFAIL:
	  return 1;
	default:
	  gSystem->Sleep( SLEEP_TIME );
	}
    }
  return 1;
}
