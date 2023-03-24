from distutils.core import setup, Extension

module1 = Extension(
	'sortingMethods', 
	 sources = ['sortingMethods.c'] 
)

setup(
	name = 'sortingMethods',              
	version = '1.1.1',               
	description = 'Simple module', 
	ext_modules= [module1]         
)