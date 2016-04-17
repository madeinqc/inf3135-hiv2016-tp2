# -*- coding: utf-8 -*-
''' 
Fichier python qui test la validité des cartes tmx disponibles dans le répertoire assets.
Pour changer de répertoire, modifier la variable path à la fin du fichier. 
''' 
import pytmx
import os
import glob

''' 
CONDITIONS DE VALIDITÉ:
	Toute tuile doit reposer sur une tuile de sable, terre ou gason seulement a l'exeption d'une tuile de terre qui peut être sur une tuile d'eau (pont).
	Au niveau 0, une tuile peut être sur une tuile vide si celle-ci est dans l'axe transitoire.
	Il est nécessaire d'avoir une et une seule maison par carte.
	Il est nécessaire d'avoir au moins une roche par carte.  
'''

''' ---------------------------------------------------------------------------------
--	Méthodes pour test seulement 
--------------------------------------------------------------------------------- '''
def print_GID_by_layer():
	''' Imprime les tuiles diponibles dans chaque niveau avec le GID et propriétés. '''
	tileSet = set()

	for noLayer in data.visible_tile_layers:
		print noLayer
		for tile in data.get_tile_properties_by_layer(noLayer):
			print tile 	
			tileSet.add(tile[0])
	tileSet = sorted(tileSet)

	o = [(i,data.get_tile_properties_by_gid(i)) for i in tileSet]

def print_GID_by_map():
	''' Imprime les tuiles diponibles dans la carte avec le GID et propriétés. '''
	tileSet = set()

	for noLayer in data.visible_tile_layers:
		for tile in data.get_tile_properties_by_layer(noLayer):	
			tileSet.add(tile[0])
	tileSet = sorted(tileSet)

	o = [(i,data.get_tile_properties_by_gid(i)) for i in tileSet]

	for item in o:
		print(item)
''' -------------------------------------------------------------------------------- '''

def get_set_GID():
	''' Retourne un set de tous les GIDs diponibles dans la carte. '''
	tileSet = set()

	for noLayer in data.visible_tile_layers:
		for tile in data.get_tile_properties_by_layer(noLayer):
			tileSet.add(tile[0])
	tileSet = sorted(tileSet)
	return tileSet

def get_map_size():
	''' Retourne une liste indiquant la largeur et la heuteur de la carte.'''
	locationList = []
	tileSet = get_set_GID()
	for gid in tileSet:
		locationList.extend(list(data.get_tile_locations_by_gid(gid)))
	width = max(locationList, key=lambda item: item[0])[0] +1
	height = max(locationList, key=lambda item: item[1])[1] +1
	return [width, height]

def get_tile_dict():
	''' Retourne un dictionnaire qui a pour cle le nom de la tuile et pour valeur le GID correspondant.'''
	tileSet = get_set_GID()
	tileDict = dict((data.get_tile_properties_by_gid(i)['source'][:-4], i) for i in tileSet)
	return tileDict

def get_dict_by_GID(gid):
	''' Retourne le le nom correspondant au GID demandé.'''
	tileSet = get_set_GID()
	tileDict = dict((i, data.get_tile_properties_by_gid(i)['source'][:-4]) for i in tileSet)
	tileDict[0] = 'empty'
	return tileDict[gid]

def get_dict_by_type(name):
	''' Retourne le le GID correspondant au nom demandé.'''
	tileDict = get_tile_dict()
	tileDict['empty'] = 0
	return tileDict[name]

def validate_level0():
	''' Verifie que le level 0 ait seulement des tuiles valides (eau, terre, sable et gazon). Retourne False si invalide. '''
	tileSet = set()
	tileAllowed = [1, 2, 3, 4, 5, 6, 7]
	for tile in data.get_tile_properties_by_layer(0):
		tileSet.add(tile[0])
	if tileSet.difference(tileAllowed) != set():
		return False 
	else:
		return True

def is_tile_type(tile, tileType):
	''' Retourne True si le type de la tuile est celui demandé. ''' 
	tileGID = data.get_tile_gid(tile[0], tile[1], tile[2])
	tileName = get_dict_by_GID(tileGID)
	if tileName == tileType:
		return True
	else:
		return False

def is_valide_tile(tile):
	''' Retourne False si la tuile n'est pas valide. 
	La tuile est valide seulement si elle est sur la terre, sur du sable ou sur du gazon a l'exeption de la terre qui peu etre sur l'eau. '''
	temp = list(tile)
	temp[2] -= 1
	underTile = tuple(temp)
	temp[2] += 1

	if not is_tile_type(underTile, 'grass') and not is_tile_type(underTile, 'sand') and not is_tile_type(underTile, 'earth'):
		if is_tile_type(underTile, 'empty'):
			if underTile[0]+1 % 15 == 0 or underTile[1]+1 % 15 ==0:
				return True
		elif is_tile_type(tile, 'earth') and is_tile_type(underTile, 'water'):
			return True
		else:
			print '%s of type %s' %(str(underTile), str(get_dict_by_GID(data.get_tile_gid(underTile[0], underTile[1], underTile[2]))))
			print '%s of type %s' %(str(tile), str(get_dict_by_GID(data.get_tile_gid(tile[0], tile[1], tile[2]))))
			return False
	return True

def validate_levels():
	''' Recupere chaque tuple de tuile qui n'est pas au niveau 0. Pour chaque tuile récuperée, on appelle la function is_valide_tile(). 
	Retourne False si une tuile est invalide.'''
	locationList = []
	tileSet = get_set_GID()
	for gid in tileSet:
		locationList.extend(list(data.get_tile_locations_by_gid(gid)))
	locationList = filter(lambda x: x[2] != 0, locationList) #enleve les tuples du level 0
	while locationList != []:
		tile = locationList.pop()
		if not is_valide_tile(tile):
			print " Position error: %s " %(str(tile))
			return False
	return True


def is_map_complete():
	''' Vérifie le nombre de maisons et roches dans la carte. Retourne False is la carte est incomplete ou invalide.'''
	elemList = []
	elemList.extend(list(data.get_tile_locations_by_gid(get_dict_by_type('house'))))
	if len(elemList) != 1:
		return False
	elemList.pop()
	elemList.extend(list(data.get_tile_locations_by_gid(get_dict_by_type('rock'))))
	if len(elemList) < 1:
		return False
	return True

def continuous_levels():
	''' Vérifie le nombre de niveaux consécutifs dans la carte. Retourne False s'il n'y a pas 4 niveaux consécutifs. '''
	layerList = list(data.visible_tile_layers)
	if len(layerList) != 4:
		return False
	for i in range(len(layerList) -2):
		if i+1-i != 1:
			return False
	return True

def validate_size():
	''' Vérifie que la largeur et la longueur de la carte permet d'avoir des sous-cartes de dimention 14x14 avec des tules de transition entre chanque sous-carte.
	Retourne False si la carte a des dimentions invalides.'''
	width = get_map_size()[0]
	height = get_map_size()[1]
	if width // 14 != width % 14 +1:
		return False
	elif (height // 14 != height % 14 +1):
		return False
	else:
		return True
	return True

def main(path):
	''' Pour chaque fichier .tmx dans le repertoire, verifie la validité et affiche le message approprié. '''
	if not continuous_levels():
		print '%s is invalid! It is required to have 4 continuous levels.' % path
	elif not validate_size():
		print '%s is invalid! The map size is not valid.' % path
	elif not validate_level0():
		print '%s is invalid! Level 0 contains invalid tiles.' % path
	elif not validate_levels():
		print '%s is invalid! Position Error.' % path
	elif not is_map_complete():
		print '%s is invalid! Missing a required element.' % path
	else:
		print '%s is valid.' % path

path = 'assets/'
for tmx_map in glob.glob(os.path.join(path, '*.tmx')):
	data = pytmx.TiledMap(tmx_map)
	main(tmx_map)
