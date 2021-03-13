# Installs Mipt-RTOS headers, sources and utilities into appropriate directories
# Invoked by make
# Option -u uninstall library

#  Note. Directory for headers and sources is created and deleted
# automatically, but binaries are stored in an existing system
# directory, which won't be deleted (because there could be other files)
LIB_HEADERS_PATH="/usr/local/include/Mipt-RTOS"
LIB_SOURCES_PATH="/usr/local/lib/Mipt-RTOS"

LIB_RTOS_CONFIG_BIN="/usr/local/bin/rtosconfig"

function install_lib {
	mkdir $LIB_HEADERS_PATH												\
	&& cp rtoslib/include/* $LIB_HEADERS_PATH							\
	&& echo "Mipt-RTOS headers installed into" $LIB_HEADERS_PATH		\
	&& mkdir $LIB_SOURCES_PATH											\
	&& cp rtoslib/src/* $LIB_SOURCES_PATH								\
	&& echo "Mipt-RTOS sources installed into" $LIB_SOURCES_PATH		\
	|| echo "Oops, something went wrong. Installation failed."
}

function install_bins {
	cp rtosconfig/build/rtosconfig $LIB_RTOS_CONFIG_BIN						\
	&& echo "Mipt-RTOS config parser is installed as" $LIB_RTOS_CONFIG_BIN	\
	|| echo "Oops, something went wrong. Installation failed."
}

function is_lib_installed {
	test -d $LIB_HEADERS_PATH || test -d $LIB_SOURCES_PATH || test -f $LIB_RTOS_CONFIG_BIN
	return $?
}

function uninstall_all {
	# user will see error if deletion failed (unlike rm -rf)
	test -d $LIB_HEADERS_PATH && rm -r $LIB_HEADERS_PATH
	test -d $LIB_SOURCES_PATH && rm -r $LIB_SOURCES_PATH
	test -f $LIB_RTOS_CONFIG_BIN && rm $LIB_RTOS_CONFIG_BIN
	return 0
}

function list_all_files {
	echo "directories:"
	test -d $LIB_HEADERS_PATH && echo "	" $LIB_HEADERS_PATH
	test -d $LIB_SOURCES_PATH && echo "	" $LIB_SOURCES_PATH
	echo "executables:"
	test -f $LIB_RTOS_CONFIG_BIN && echo "	" $LIB_RTOS_CONFIG_BIN
	return 0
}

if getopts u flag # uninstall libraty
then
	if $(is_lib_installed)
	then
		echo "These files will be deleted:"
		list_all_files
		uninstall_all && echo "Mipt-RTOS lib uninstalled. Hope you will be back!"
	else
		echo "Mipt-RTOS lib is not found. Probably it is already deleted"
	fi
	exit
fi

if $(is_lib_installed)
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