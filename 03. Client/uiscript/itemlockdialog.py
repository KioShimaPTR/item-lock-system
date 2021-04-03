# Author: Bahadýr Bozdað or Cosby or KioShima
# File name: itemlockdialog.py

import uiScriptLocale

window = {
	"name" : "ItemLockDialog",
	"style" : ("movable", "float",),

	"x" : SCREEN_WIDTH - 400,
	"y" : 70 * 800 / SCREEN_HEIGHT,

	"width" : 320,
	"height" : 175,

	"children" :
	(
		{
			"name" : "Board",
			"type" : "board",
			"style" : ("attach",),

			"x" : 0,
			"y" : 0,

			"width" : 320,
			"height" : 175,

			"children" :
			(
				{
					"name" : "TitleBar",
					"type" : "titlebar",
					"style" : ("attach",),

					"x" : 8,
					"y" : 8,

					"width" : 305,
					"color" : "gray",

					"children" :
					(
						{
							"name" : "TitleName",
							"type" : "text",
							"text" : "Ýtem Kilit",
							"horizontal_align" : "center",
							"text_horizontal_align" : "center",
							"x" : 0,
							"y" : 3,
						},
					),
				},
				{
					"name": "lockText",
					"type": "text",
						"x": 0,
						"y": 37,
						"text_horizontal_align": "center",
						"horizontal_align": "center",
						"text": "text2",
					},
					{
						"name": "lockText2",
						"type": "text",
						"x": 0,
						"y": 50,
						"text_horizontal_align": "center",
						"horizontal_align": "center",
						"text": "text2",
					},
				{
					"name": "item_lock_pw_body",
					"type": "image",

					"x": 0,
					"y": 76,
					"horizontal_align": "center",
					"image": "d:/ymir work/ui/pet/pet_incu_001.tga",

					"children":
					(
						{
							"name": "item_lock_pw_title",
							"type": "text",

							"x": 80,
							"y": 7,

							"text": "Ýtem Kilit Þifreniz",
							"text_horizontal_align": "center"
						},
						{
							"name": "item_lock_pw_value",
							"type": "editline",

							"x": 15,
							"y": 29,

							"width": 60,
							"height": 18,
							"only_number": 1,
							"input_limit": 6,
							"secret_flag": 1,
						},
					),
				},
				{
					"name": "accept_button",
					"type": "button",

					"x": 207-38,
					"y": 140,

					"text": "Tamam",

					"default_image": "d:/ymir work/ui/public/large_button_01.sub",
					"over_image": "d:/ymir work/ui/public/large_button_02.sub",
					"down_image": "d:/ymir work/ui/public/large_button_03.sub",
				},
				{
					"name": "change_pw_button",
					"type": "button",

					"x": 63,
					"y": 140,

					"text": "Þifre Deðiþtir",
					"default_image": "d:/ymir work/ui/public/large_button_01.sub",
					"over_image": "d:/ymir work/ui/public/large_button_02.sub",
					"down_image": "d:/ymir work/ui/public/large_button_03.sub",
				},
			),
		},
	),
}