#!/usr/bin/python

import sys, os
import random

def getDict():
  dict = {}
  dict['runid'] = -1
  dict['filename'] = ''
  dict['randomseed'] = 0
  dict['numberofevents'] = 0
  return dict

def fillDict(run,runDict):
  basePath = '/axp/lnxdata304/wrk2/ltm/robj/LBNENu'
  scriptDir = basePath+'/scripts'
  logDir = basePath+'/logs'
  macroDir = basePath+'/macros'
  runDict['filedir'] = basePath+'/files'
  runDict['runid'] = run
  runDict['randomseed'] = 10*run + int(random.random()*1e10)
  runDict['numberofevents'] = 100000
  runDict['filename'] = 'NuFlux'
  runDict['scriptfile'] = scriptDir+'/RunNuFlux%04i.sh'%run
  runDict['logname'] = logDir+'/NuFlux%04i.log'%run
  runDict['macrofile'] = macroDir+'/NuFlux%04i.mac'%run
  runDict['inputcard'] = '/axp/lnxdata304/wrk2/ltm/robj/Software/LBNE/nuAncestry/inputs/CD1-CDR_Geo.input'
  runDict['physicslist'] = 'QGSP_BERT'
  runDict['handle'] = 'NuFlux%04i'%run

def ParseLine(line):
  #returns the command and the string for the dict
  command = line[0:line.find('@')]
  variable = line[line.find('@'):]
  variable = variable.strip('@')
  variable = variable.rstrip('@')
  return command, variable.lower()

def getWrapperLines(runDict):
  lines = []
  lines.append('cd ${TMPDIR}')
  lines.append('cp '+runDict['inputcard'] + ' .')
  lines.append('cp '+runDict['macrofile'] + ' .')
  cmdLine = '${G4BIN}/Linux-g++/g4lbne -p ' + runDict['physicslist']
  cmdLine += ' -i '+runDict['inputcard'] + ' ' + runDict['macrofile']
  lines.append(cmdLine)
  lines.append('cp ${TMPDIR}/*root ' +runDict['filedir'])
  return lines

def main():

  runs = []
  if len(sys.argv) > 1:
    if len(sys.argv) == 2:
      runs.append(int(sys.argv[1]))
    elif len(sys.argv) == 3:
      runs = range(int(sys.argv[1]),int(sys.argv[2]))
    elif len(sys.argv) > 3:
      runs = [int(i) for i in sys.argv[1:]]

  basePath = '/axp/lnxdata304/wrk2/ltm/robj/LBNENu'
  runDict = getDict()
  

  toSubmit = []
  
  for run in runs:
    fillDict(run, runDict)
    template = open('macros/nuTemplate.mac','r')
    outLines = []
    outMacroFile = open(runDict['macrofile'],'w')
    for line in template:
      line = line.rstrip('\n')

      if '@' not in line:
        outLines.append(line)
      else:
        command, var = ParseLine(line)
        outLines.append(command+' '+str(runDict[var]))

    for line in outLines:
      outMacroFile.write(line+'\n')
    outMacroFile.close()
    template.close()
    wrapperLines = getWrapperLines(runDict)
    wrapper = open(runDict['scriptfile'],'w')
    for line in wrapperLines:
      wrapper.write(line+'\n')
    wrapper.close()
    os.system('chmod 744 '+runDict['scriptfile'])
    subLine = 'Qsub -e -l lnxfarm -o '+runDict['logname'] 
    subLine += ' -N ' + runDict['handle'] + ' ' + runDict['scriptfile']
    toSubmit.append(subLine)

  for line in toSubmit:
    print line
    os.system(line)

if __name__ == '__main__':
  main()
