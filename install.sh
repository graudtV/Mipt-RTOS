# Installs Mipt-RTOS headers, sources and utilities into appropriate directories
# Invoked by make
# Option -u uninstall library

LIB_HEADERS_PATH="/usr/local/include/Mipt-RTOS"
LIB_SOURCES_PATH="/usr/local/lib/Mipt-RTOS"
LIB_BINS_PATH="/usr/local/bin/Mipt-RTOS"

function install_lib {
	mkdir $LIB_HEADERS_PATH											\
	&& cp rtoslib/include/* $LIB_HEADERS_PATH						\
	&& echo "Mipt-RTOS headers installed into" $LIB_HEADERS_PATH	\
	&& mkdir $LIB_SOURCES_PATH										\
	&& cp rtoslib/src/* $LIB_SOURCES_PATH							\
	&& echo "Mipt-RTOS sources installed into" $LIB_SOURCES_PATH	\
	|| echo "Oops, something went wrong. Installation failed."
}

function install_bins {
	mkdir $LIB_BINS_PATH											\
	&& cp config_parser/build/rtosconfig $LIB_BINS_PATH				\
	&& echo "Mipt-RTOS utilities installed into" $LIB_BINS_PATH		\
	|| echo "Oops, something went wrong. Installation failed."
}

function uninstall_all {
	# user will see error if deletion failed
	test -d $LIB_HEADERS_PATH && rm -r $LIB_HEADERS_PATH
	test -d $LIB_SOURCES_PATH && rm -r $LIB_SOURCES_PATH
	test -d $LIB_BINS_PATH && rm -r $LIB_BINS_PATH	
}

if getopts u flag # uninstall libraty
then
	uninstall_all
	echo "Mipt-RTOS lib uninstalled. Hope you will be back!"
	exit
fi

if test -d $LIB_HEADERS_PATH || test -d $LIB_SOURCES_PATH || test -d $LIB_BINS_PATH # library already exists
then
	echo
	read -p "Mipt-RTOS lib is already installed. Reinstall it? (y or n) " -n 1 -r
	echo
	if [[ $REPLY =~ ^[Yy]$ ]]
	then
		uninstall_all
	else
		echo "Nothing done. Have a nice day!"
		echo
		exit
	fi
fi
	echo
	install_lib
	install_bins
	echo