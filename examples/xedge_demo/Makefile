############################################################################
# apps/examples/xedge_demo/Makefile
#
# Licensed to the Apache Software Foundation (ASF) under one or more
# contributor license agreements.  See the NOTICE file distributed with
# this work for additional information regarding copyright ownership.  The
# ASF licenses this file to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance with the
# License.  You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
# License for the specific language governing permissions and limitations
# under the License.
#
############################################################################

include $(APPDIR)/Make.defs

# Xedge Demo Application Info

PROGNAME  = $(CONFIG_EXAMPLES_XEDGE_DEMO_PROGNAME)
PRIORITY  = $(CONFIG_EXAMPLES_XEDGE_DEMO_PRIORITY)
STACKSIZE = $(CONFIG_EXAMPLES_XEDGE_DEMO_STACKSIZE)
MODULE    = $(CONFIG_EXAMPLES_XEDGE_DEMO)

# Xedge Demo Application Sources - using BAS from netutils/xedge

MAINSRC = xedge_main.c $(APPDIR)/netutils/xedge/BAS/src/BAS.c $(APPDIR)/netutils/xedge/BAS/src/dlmalloc.c $(APPDIR)/netutils/xedge/BAS/src/arch/Posix/ThreadLib.c $(APPDIR)/netutils/xedge/BAS/src/arch/NET/generic/SoDisp.c $(APPDIR)/netutils/xedge/BAS/src/DiskIo/posix/BaFile.c $(APPDIR)/netutils/xedge/BAS/examples/xedge/src/xedge.c $(APPDIR)/netutils/xedge/BAS/examples/xedge/XedgeZip.c

include $(APPDIR)/Application.mk
