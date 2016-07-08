TEMPLATE = subdirs

# main libs to create
libnbodysim.subdir = projects/libnbodysim

# tests
tests.subdir = projects/tests
tests.depends += libnbodysim

# examples
#example.subdir = projects/examples/
#example.depends += libnbodysim

SUBDIRS += libnbodysim

SUBDIRS += tests
#SUBDIRS += example


CONFIG += silent

CONFIG += warn_on
