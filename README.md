# Qt-Creator-Recipe-Planner

### Description
Simple recipe planner for storing data about the recipes and creating shopping lists.

### Main screen

-Displays list of all available recipes
-Has buttons to Add/Edit/Delete recipes

### Entry dialog

-User may Add new or Edit existing recipe
-Recipe consist of multiline description and list of ingredients
-Each ingredient has name, quantity and unit where:
 -name is a multiword string (like bread flour)
 -quantity is a float number (like 1.0)
 -unit is a multiword string (any string is treated as a unit - so "red balbinka" is also a unit)

### Menu Dialog

User may create a list of recipes to be cooked, for instance:

-omlette x3
-pizza 

and program will compute sorted list of required ingredients to buy:

-active dry yeast: 0.25 ounce
-egg: 7.0 pcs
-flour: 2.5 cups
-olive oil:2.0 tablespoons
-salt: 3.0 pinch
-salt: 1.0 teaspoon
-water: 0.09 l

only compatible (=equal strings) units are summed up (see eggs with pcs) - if units are not compatible ingredients are presented separately (see salt)

### Main window view
<img width="600" src="https://github.com/mkaniukk/Qt-Creator-Recipe-Planner/blob/main/assets/mainwindow.png">

### Add window view
<img width = "600" src="https://github.com/mkaniukk/Qt-Creator-Recipe-Planner/blob/main/assets/addwindow.png">
  
### Edit window view
<img width = "600" src="https://github.com/mkaniukk/Qt-Creator-Recipe-Planner/blob/main/assets/editwindow.png">
  
### Shopping list window view
<img width = "600" src="https://github.com/mkaniukk/Qt-Creator-Recipe-Planner/blob/main/assets/shoppinglistwindow.png">
