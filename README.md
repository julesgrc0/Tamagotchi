# Tamagotchi

## Run


```cmd
start Tamagotchi.exe [type_id = 1]
```

## Config

* assets/config/user.json
```json
// Remove all comments 

{
	"music" : 
	{
		"active" : true, 
		"pitch" : 1.0, 
		"volume" : 100
	},
	"window" : 
	{
		"VerticalSync" : false,
		"alwaysOnTop" : false,
		"console" : true, 
		"position" : 
		{
			"x" : -1,
			"y" : -1 
		},
		"showFPS" : true, 
		"titlebar" : true 
	}
}
```

* show/hide console
* show/hide titlebar
* active/disable background music

> window position

x or y = -1<br>
screen center x or y <br>
x or y = -2<br>
screen right x or y<br>
<br>
x = 0...1920
<br>
y = 0...1080



## Assets

Make your own assets and respect their size, name and number.
* assets/type_x
    * energie 4
    * angry 7
    * happy 5
    * loop 16
    * sick 4
    * sleep 9 
    * static 6
    * waiting 5
* assets/music
    * background (WAV)
* icons 8
* background 3 * x

