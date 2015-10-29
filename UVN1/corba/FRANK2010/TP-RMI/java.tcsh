


setenv PATH $RACINE_JAVA/bin:$PATH


if ($?CLASSPATH) then  
	setenv CLASSPATH .:classes:$CLASSPATH
else
	setenv CLASSPATH .:classes:
endif


if ($?LD_LIBRARY_PATH) then  
	setenv LD_LIBRARY_PATH $RACINE_JAVA/lib:$LD_LIBRARY_PATH
else
	setenv LD_LIBRARY_PATH $RACINE_JAVA/lib
endif






