import os
import string
import sys

from SCons.Script.SConscript import BuildDefaultGlobals
globals().update(BuildDefaultGlobals())


def ParseConfig(env, command, options):
   "Parses xxx-config style output for compilation directives"

   # Run the command
   where = WhereIs(command)
   if not where:
      print '%s not found in PATH' % command
      sys.exit(-1)
   cmd = where + ' ' + string.join(options)
   params = string.split(os.popen(cmd).read())

   # Parse its output
   idx = 0
   while idx < len(params):
      arg = params[idx]
      idx = idx + 1
      
      switch = arg[0:1]
      option = arg[1:2]
      if switch == '-':
         if option == 'I':
            env.Append(CPPPATH = [arg[2:]])
         elif option == 'L':
            env.Append(LIBPATH = [arg[2:]])
         elif option == 'l':
            env.Append(LIBS = [arg[2:]])
         elif arg[0:11] == '-Wl,-rpath,':
            env.Append(LINKFLAGS = [arg])
         elif option == 'B':
            env.Append(CXXFLAGS = ['-B', params[idx]])
            idx = idx + 1
         else:
            env.Append(CXXFLAGS = [arg])
      else:
         # Must be a static library, add it to the libs
         env.Append(LIBS = [arg])


def SetupGLText(env):
   if string.find(sys.platform, 'irix') != -1:
      env.Append(CPPPATH = [Dir('third-party-sgi/include')],
                 LIBPATH = [Dir('third-party-sgi/lib32')],
                 LIBS = ['gltext'])
   else:
      env.Append(LIBS = ['gltext'])



def SetupJuggler(env):
   ParseConfig(env, 'vrjuggler-config', ['--cxxflags --libs --extra-libs'])
