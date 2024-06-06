
import json
import base64
import requests
from io import BytesIO
from PIL import Image, ImageDraw, ImageFont
import random
import time

random.seed(int(time.time()))
FONT_SIZE: int = 96
IMG_SIZE: int = 128
fnt = ImageFont.truetype("./RobotoMono-Bold.ttf", FONT_SIZE)

def random_color_generator():
    r = random.randint(0, 255)
    g = random.randint(0, 255)
    b = random.randint(0, 255)
    return (r, g, b)

def generateThumbs(title: str) -> str:
    color = random_color_generator()
    brightness = color[0]*0.299 + color[1]*0.587 + color[2]*0.114 
    
    if brightness > 180:
      textColor = (0,0,0)
    else:
      textColor = (255,255,255)

    out = Image.new("RGBA", (IMG_SIZE, IMG_SIZE), color = (255, 255, 255, 0))

    letter = title.upper()[0]
    
    d = ImageDraw.Draw(out)
    d.font = fnt
    x, y, observed_width, observed_height = d.textbbox(xy=(0, 0), text=letter, font=fnt)
    d.rounded_rectangle(((0, 0), (IMG_SIZE, IMG_SIZE)), 8, fill=color)
    d.text(((IMG_SIZE-observed_width - x)/2, (IMG_SIZE-observed_height - y)/2), letter, fill=textColor)
    # out.show()
    img_byte_arr = BytesIO()
    out.save(img_byte_arr, format='PNG')
    img_byte_arr = img_byte_arr.getvalue()
    return "data:image/png;base64," + base64.b64encode(img_byte_arr).decode("utf-8")    

def findImage(items: list) -> str | None:
    for item in items:
        icon = fetchImage(item)
        if icon != None:
            return icon
    return None

def fetchImage(link: str | None) -> str | None:
    if link == None: return None

    try:
        r = requests.get(link, timeout=5)
        if not r.ok:
            return None

        img = Image.open(BytesIO(r.content), formats=["png", "jpeg"])
        width, height = img.size
        print(f"{width}x{height}: {link}")
        if width != height or width > 1024 or height > 1024 or width < 128 or height < 128:
            return None
        
        img_byte_arr = BytesIO()
        img.save(img_byte_arr, format='PNG')
        img_byte_arr = img_byte_arr.getvalue()

        return "data:image/png;base64," + base64.b64encode(img_byte_arr).decode("utf-8")
    except Exception as ex:
        print("exception", link, ex)
    
    return None

apps_items = {}
 
with open("apps.json", "r") as jsonFile:
    apps_items = json.loads(jsonFile.read())

items = apps_items["items"]

count = len(items)
i = 0
for item in items:
    i = i + 1
    p = (i*100.0/count)
    print(f"{p}% {i} / {count}")
    icon = item.get("icon", None)
    icons = item.get('icons', [])

    icon = fetchImage(icon)
    if icon == None or icon == "":
        icon = findImage(icons)
    if icon == None:
        icon = generateThumbs(item.get("title"))

    item["icon"] = icon
    item.pop("icons", None)

    if i % 10 == 0:
        apps_items["items"] = items
        with open("apps2.json", "w") as jsonFile:
            jsonFile.write(json.dumps(apps_items, indent=2))


apps_items["items"] = items
with open("apps2.json", "w") as jsonFile:
    jsonFile.write(json.dumps(apps_items, indent=2))
