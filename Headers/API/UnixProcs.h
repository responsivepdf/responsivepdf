/*************************************************************************
* WARNING: All additions to this file must go at the end of the file.
* This file is #included to build a table of function pointers (an HFT).
* All components which make use of this HFT rely on the order and
* positioning of these functions (e.g. plug-ins). Adding entries in the 
* middle of this file or modifying existing entries will cause these 
* components to break.
**************************************************************************/

/*********************************************************************

 ADOBE SYSTEMS INCORPORATED
 Copyright (C) 1996-2006 Adobe Systems Incorporated
 All rights reserved.

 NOTICE: Adobe permits you to use, modify, and distribute this file
 in accordance with the terms of the Adobe license agreement
 accompanying it. If you have received this file from a source other
 than Adobe, then your use, modification, or distribution of it
 requires the prior written permission of Adobe.

 ---------------------------------------------------------------------

 UnixProcs.h

 - Catalog of functions exported by the Unix Viewer.

*********************************************************************/


/**
	Not Supported. If you wanted this for a dialog, ADM is the preferred way now. 
	@ see UnixAppGetAppShellGtkWidget
	@since PI_UNIX_VERSION >= 0x00020000
*/
NOPROC(UnixAppGetAppShellWidget)

/**
	Not supported.
	@since PI_UNIX_VERSION >= 0x00020000
*/
NOPROC(UnixAppLoadPlugInAppDefaults)

/**
	Not supported. If you wanted this for the selection server Gtk is the preferred way.
	@since PI_UNIX_VERSION >= 0x00020000
*/
NOPROC(UnixAppClipboardGetItemId)

/**
	Not supported. Not required with Gtk. Try <code>gtk_main</code>, or better still, <code>g_main_context_iteration(NULL, FALSE)</code>.
	@since PI_UNIX_VERSION >= 0x00020000
*/
NOPROC(UnixAppDispatchEvent)

/**
	Not supported. Not required with Gtk. Try <code>gtk_main</code>, or better still, <code>g_main_context_iteration(NULL, FALSE)</code>.
	@since PI_UNIX_VERSION >= 0x00020000
*/
NOPROC(UnixAppProcessEvent)

/**
	Not supported.
	@since PI_UNIX_VERSION >= 0x00020000
*/
NOPROC(UnixAppWaitForWm)

/**
	Gets the client's file name. The directory can be used to 
	find auxiliary files for that client. 

	<p>The Acrobat viewer searches all the directories specified 
	in the <code>systemPlugInPath</code> and <code>userPlugInPath</code> resources to 
	find clients. </p>

	@param thePI The gExtensionID extension registering the 
	client.
	@return The client's file name. The string returned must not be altered 
	or freed. 
	@since PI_UNIX_VERSION >= 0x00020000
*/
NPROC(char *, UnixAppGetPlugInFilename, (ASExtension thePI))

/**
	Gets the home directory of the user running the Acrobat 
	viewer. If the <code>HOME</code> environment variable is set, its value 
	is returned. Otherwise the method looks in the <code>passwd</code> database. 
	
	@return The user's home directory. The string returned by this method 
	must not be altered or freed. 
	@see UnixSysGetCwd 
	@see UnixSysGetHostname 
	@since PI_UNIX_VERSION >= 0x00020000
*/
NPROC(char *, UnixSysGetHomeDirectory, (void))

/**
	Gets the directory in which the Acrobat viewer is installed. 
	The launch shell script sets the installation directory 
	in the environment variable <code>ACRO_INSTALL_DIR</code>. 

	<p>Auxiliary files can be found by concatenating the installation 
	directory with the configuration name sub-directory: </p>

	<p><code>installation_dir/config_name </code></p>

	@return The Acrobat viewer's installation directory. 
	@see UnixSysGetHomeDirectory 
	@since PI_UNIX_VERSION >= 0x00020000
*/
NPROC(char *, UnixSysGetInstallDirectory, (void))

/**
	Gets the Acrobat viewer's configuration name. The name is 
	one of the following: 

	<TABLE rules="all" cellspacing="1">
	<TR><TH>Operating system</TH><TH>Configuration name</TH></TR>
	<TR><TD>SunOS</TD><TD><code>sparcsun</code></TD></TR>
	<TR><TD>Solaris</TD><TD><code>sparcsolaris</code></TD></TR>
	<TR><TD>HP-UX</TD><TD><code>hppahpux</code></TD></TR>
	<TR><TD>Linux</TD><TD><code>intellinux</code></TD></TR>
	<TR><TD>IBM AIX</TD><TD><code>rs6000aix</code></TD></TR>
	</TABLE>

	<p>The Acrobat viewer's launch shell script uses <code>uname</code> to set 
	the configuration name in the environment variable <code>ACRO_CONFIG</code>. </p>
	
	<p>Auxiliary files can be found by concatenating the installation 
	directory with the configuration name sub-directory: </p>

	<p><code>installation_dir/config_name </code></p>

	@return The Acrobat viewer's configuration name. 
	@since PI_UNIX_VERSION >= 0x00020000
*/
NPROC(char *, UnixSysGetConfigName, (void))

/**
	Gets the host name. 
	@return The host name. 
	@see UnixSysGetHomeDirectory 
	@since PI_UNIX_VERSION >= 0x00020000
*/
NPROC(char *, UnixSysGetHostname, (void))

/**
	Gets the temporary file directory specified by the user. 
	The default is <code>/tmp</code>. 
	@return The temporary file directory. 
	@see UnixSysGetHomeDirectory 
	@since PI_UNIX_VERSION >= 0x00020000
*/
NPROC(char *, UnixSysGetTempFileDirectory, (void))

/**
	Gets the current working directory. This method tries to 
	eliminate <code>automounter tmp</code> directories and symbol links. 
	Using <code>stat</code>, it checks if the environment variable <code>PWD</code> specifies 
	the same directory returned by <code>getcwd</code>. 
	@return The current working directory. 
	@exception genErrNoMemory 
	@see UnixSysGetHomeDirectory 
	@since PI_UNIX_VERSION >= 0x00020000
*/
NPROC(char *, UnixSysGetCwd, (void))

/**
	Not supported. The strings can be handled as resources.
	@since PI_UNIX_VERSION >= 0x00020000
*/
NOPROC(UnixSysGetString)

/**
	Not supported. 
	@since PI_UNIX_VERSION >= 0x00020000
*/
NOPROC(UnixSysGetCursor)

/**
	Not supported. The Icons should be bundled as a resource.
	@since PI_UNIX_VERSION >= 0x00020000
*/
NOPROC(UnixSysGetIcon)

/**
	Not supported.
	@since PI_UNIX_VERSION >= 0x00020000
*/
NOPROC(UnixSysGetPixmap)

/** 
	Not supported.
	@since PI_UNIX_VERSION >= 0x00020000
*/
NOPROC(UnixAppAddModifierCallback)

/**
	Not supported.
	@since PI_UNIX_VERSION >= 0x00020000
*/
NOPROC(UnixAppRemoveModifierCallback)


/**
	Not supported.
	@since PI_UNIX_VERSION >= 0x00020000
*/
NOPROC(UnixSysPrefInit)

/**
	Not supported.
	@since PI_UNIX_VERSION >= 0x00020000
*/
NOPROC(UnixSysPrefUpdate)

/**
	Gets the topmost widget of the application. The window is of the type GtkWindow.
	@return The Acrobat viewer's application shell widget. 
	@since PI_UNIX_VERSION >= 0x00020000
*/
NPROC(GtkWidget *, UnixAppGetAppShellGtkWidget, (void))

 
 
/**
        Returns an appropriate top-level parent window, from which a modal dialog can be parented.
        @param avdoc IN The currently active document if known. It can be <code>NULL</code>.
        @return An appropriate parent will be determined and returned. This will be a top-level GTK window.
*/
NPROC(GtkWidget * , UnixAppGetModalParent, (AVDoc avdoc))


/**
        Returns an appropriate top-level parent window off which a dialog can be parented.
        @return An appropriate parent will be determined and returned. This will be a top-level GTK window.
*/
NPROC(GtkWidget * , UnixAppGetModelessParent, (void))
