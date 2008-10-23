#!/usr/bin/env ruby

# -------------------------------------------------------------------  #
# Copyright (c) 2007-2008 Hanzo Archives Limited.                      #
#                                                                      #
# Licensed under the Apache License, Version 2.0 (the "License");      #
# you may not use this file except in compliance with the License.     #
# You may obtain a copy of the License at                              #
#                                                                      #
#     http//www.apache.org/licenses/LICENSE-2.0                        #
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
#     http//www.hanzoarchives.com/                                     #
#                                                                      #
# You may find more information about the WARC Tools project at        #
#                                                                      #
#     http//code.google.com/p/warc-tools/                              #
# -------------------------------------------------------------------  #


$: << "../../lib/private/plugin/ruby"
$: << "/usr/local/warc-tools/ruby"

require 'warctools'
require 'wfile'
require 'wrecord'

include Warctools

def dumpWarc(filename)


  w = WFile.new(filename, 1024 * 1024 * 1024,
                Warctools::WARC_FILE_READER, 
                Warctools::WARC_FILE_DETECT_COMPRESSION, ".")


  puts "%-16s %-12s %-22s %-50s" % ["Time Stamp", "Offset", "Content Type", "Url"]
  while (w.hasMoreRecords()) do
    r =  w.nextRecord()

    puts "%-16s %-12s %-22s% -50s" % [r.getDate, "#{r.getOffset}", r.getContentType, r.getTargetUri]

    r.destroy()
  end
end

def main()

  if (ARGV.size ==0)
    puts "Usage: #{__FILE__} warcfile"
  end

  dumpWarc(ARGV[0])
end

main()
