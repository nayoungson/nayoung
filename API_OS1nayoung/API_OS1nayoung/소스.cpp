#include <Windows.h>

/**
BOOL TESTmain()
{
  BOOL bResult;                   // generic Boolean value
  ULONG_PTR NumberOfPages;        // number of pages to request
  ULONG_PTR NumberOfPagesInitial; // initial number of pages requested
  ULONG_PTR *aPFNs;               // page info; holds opaque data
  PVOID lpMemReserved;            // AWE window
  SYSTEM_INFO sSysInfo;           // useful system information
  int PFNArraySize;   
  // memory to request for PFN array
  #define MEMORY_REQUESTED 1024*1024
  GetSystemInfo(&sSysInfo);  // fill the system information structure

  _tprintf(_T("This computer has page size %d.\n"), sSysInfo.dwPageSize);

  // Calculate the number of pages of memory to request.

  NumberOfPages = MEMORY_REQUESTED/sSysInfo.dwPageSize;
  _tprintf (_T("Requesting %d pages of memory.\n"), NumberOfPages);

  // Calculate the size of the user PFN array.

  PFNArraySize = NumberOfPages * sizeof (ULONG_PTR);

  _tprintf (_T("Requesting a PFN array of %d bytes.\n"), PFNArraySize);

  aPFNs = (ULONG_PTR *) HeapAlloc(GetProcessHeap(), 0, PFNArraySize);

  if (aPFNs == NULL) 
  {
    _tprintf (_T("Failed to allocate on heap.\n"));
    return;
  }

  // Enable the privilege.

  if( ! LoggedSetLockPagesPrivilege( GetCurrentProcess(), TRUE ) ) 
  {
    return;
  }

  // Allocate the physical memory.

  NumberOfPagesInitial = NumberOfPages;
  bResult = AllocateUserPhysicalPages( GetCurrentProcess(),
                                       &NumberOfPages,
                                       aPFNs );
    
  if( bResult != TRUE ) 
  {
    _tprintf(_T("Cannot allocate physical pages (%u)\n"), GetLastError() );
    return;
  }

  if( NumberOfPagesInitial != NumberOfPages ) 
  {
    _tprintf(_T("Allocated only %p pages.\n"), NumberOfPages );
    return;
  }

  // Reserve the virtual memory.
    
  lpMemReserved = VirtualAlloc( NULL,
                                MEMORY_REQUESTED,
                                MEM_RESERVE | MEM_PHYSICAL,
                                PAGE_READWRITE );

  if( lpMemReserved == NULL ) 
  {
    _tprintf(_T("Cannot reserve memory.\n"));
    return;
  }

  // Map the physical memory into the window.
    
  bResult = MapUserPhysicalPages( lpMemReserved,
                                  NumberOfPages,
                                  aPFNs );

  if( bResult != TRUE ) 
  {
    _tprintf(_T("MapUserPhysicalPages failed (%u)\n"), GetLastError() );
    return;
  }

  // unmap
    
  bResult = MapUserPhysicalPages( lpMemReserved,
                                  NumberOfPages,
                                  NULL );

  if( bResult != TRUE ) 
  {
    _tprintf(_T("MapUserPhysicalPages failed (%u)\n"), GetLastError() );
    return;
  }

  // Free the physical pages.

  bResult = FreeUserPhysicalPages( GetCurrentProcess(),
                                   &NumberOfPages,
                                   aPFNs );

  if( bResult != TRUE ) 
  {
    _tprintf(_T("Cannot free physical pages, error %u.\n"), GetLastError());
    return;
  }

  // Free virtual memory.

  bResult = VirtualFree( lpMemReserved,
                         0,
                         MEM_RELEASE );

  // Release the aPFNs array.

  bResult = HeapFree(GetProcessHeap(), 0, aPFNs);

  if( bResult != TRUE )
  {
      _tprintf(_T("Call to HeapFree has failed (%u)\n"), GetLastError() );
  }

}
*/