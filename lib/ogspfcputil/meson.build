# Copyright (C) 2025 by Cosine / Genie
#
# Internal PFCP utilities shared across control/user-plane components.
#
# This file is part of Open5GS.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

libogspfcputil_sources = files('''
    pfcp_util.h
    pfcp_util.c
'''.split())

libogspfcputil_inc = include_directories('.')

libogspfcputil = library('ogspfcputil',
    sources : libogspfcputil_sources,
    version : libogslib_version,
    include_directories : [libogspfcputil_inc, libinc],
    dependencies : libpfcp_dep,
    install_rpath : libdir,
    install : false)

libogspfcputil_dep = declare_dependency(
    link_with : libogspfcputil,
    include_directories : [libogspfcputil_inc, libinc],
    dependencies : libpfcp_dep)