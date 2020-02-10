doxyfile = configuration_data()
doxyfile.set('OUTPUT_DIRECTORY', meson.build_root())
configure_file(input: 'Doxyfile.in', output: 'Doxyfile', configuration: doxyfile)
doxygen = find_program('doxygen', required : false)
if doxygen.found()
  message('Doxygen found')
  run_target('doc', command : [doxygen, meson.build_root() + '/doc/Doxyfile'])    
else
  warning('Documentation disabled without doxygen')
endif