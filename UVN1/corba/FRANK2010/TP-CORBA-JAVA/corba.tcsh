
setenv CORBA_HOME /usr/home/enstb1/JacORB/

setenv ANT_HOME /usr/home/enstb1/apache-ant/
setenv JACORB_HOME $CORBA_HOME

setenv PATH $ANT_HOME/bin:$JAVA_HOME/bin:$PATH
setenv PATH $JACORB_HOME/bin:$JACORB_HOME/etc:$JACORB_HOME/lib:$JACORB_HOME/classes:$JACORB_HOME/src:$PATH

setenv CLASSPATH $JACORB_HOME/classes:$JACORB_HOME/lib:$ANT_HOME/lib:.:classes




