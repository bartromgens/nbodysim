TEMPLATE = subdirs

# main lib
libnbodysim.subdir = projects/libnbodysim

# tests
tests.subdir = projects/tests
tests.depends += libnbodysim

# example
solarsystem.subdir = projects/solarsystem
solarsystem.depends += libnbodysim

SUBDIRS += libnbodysim
SUBDIRS += tests
SUBDIRS += solarsystem


CONFIG += silent

CONFIG += warn_on
