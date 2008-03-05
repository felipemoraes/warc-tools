#!/bin/bash

# -------------------------------------------------------------------  #
# Copyright (c) 2007-2008 Hanzo Archives Limited.                      #
#                                                                      #
# Licensed under the Apache License, Version 2.0 (the "License");      #
# you may not use this file except in compliance with the License.     #
# You may obtain a copy of the License at                              #
#                                                                      #
#     http://www.apache.org/licenses/LICENSE-2.0                       #
#                                                                      #
# Unless required by applicable law or agreed to in writing, software  #
# distributed under the License is distributed on an "AS IS" BASIS,    #
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or      #
# implied.                                                             #
# See the License for the specific language governing permissions and  #
# limitations under the License.                                       #
#                                                                      #
# You may find more information about Hanzo Archives at                #
#                                                                      #
#     http://www.hanzoarchives.com/                                    #
#                                                                      #
# You may find more information about the WARC Tools project at        #
#                                                                      #
#     http://code.google.com/p/warc-tools/                             #
# -------------------------------------------------------------------  #

usage () {

    echo "Check if all WARC files in a directory are valid"
    echo "Usage: $0 <-d dirname> [-c wgzip] [-v] [-h]"  >&2
    echo "       -d     : directory name containing ARC files"  >&2
    echo "       -c     : WARC files are compressed (default yes)"  >&2
    echo "       -h     : print this help message"  >&2
    echo "       -v     : output version information and exit"  >&2
    exit 1
}

# default settings
version="0.17"

while getopts hvcd: o
do
  case "$o" in
    d)   dn=$OPTARG ;;
    c)   ccomp="-c" ;;
    h)   usage ;;
    v)   echo "$0 v$version"; exit 0 ;;
    *)   usage ;;
  esac
done

if [ -z "$dn" ]; then
    echo ">> you must supply \"-d\" option" >&2
    usage
fi

if [ ! -d "$dn" ]; then
    echo ">> directory \"$dn\" doesn't exist" >&2
    usage
fi

orig_dir=$(pwd)
cd ${0%/*}/..
wvalid="`pwd`/app/warcvalidator"

if ! type $wvalid &>/dev/null; then
    echo ">> \"$wvalid\" doesn't exist" >&2
    usage
fi

for wf in `find $dn -name "*.warc*" -type "f"`;
do
  $wvalid -f $wf $ccomp &>/dev/null
  if [ $? -eq 0 ]; then
      echo "valid $wf"
  else
      echo "invalid $wf"
  fi
done 

exit 0
