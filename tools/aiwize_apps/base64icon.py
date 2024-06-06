
import traceback
import base64
import requests
from PIL import Image
from io import BytesIO



def fetchImage(link: str | None) -> str | None:
    if link == None: return None

    try:
        r = requests.get(link, timeout=5)
        print("request: ", r)
        img = Image.open(BytesIO(r.content), formats=["png", "jpeg"])
        width, height = img.size
        print(f"{width}x{height}: {link}")
        if width != height or width > 1024 or height > 1024 or width < 64 or height < 64:
            return None
        
        img_byte_arr = BytesIO()
        img.save(img_byte_arr, format='PNG')
        img_byte_arr = img_byte_arr.getvalue()

        return "data:image/png;base64," + base64.b64encode(img_byte_arr).decode("utf-8")
    except Exception as ex:
        print("exception", link, ex)
        traceback.print_exc()
    
    return None

print(fetchImage("https://www.apple.com/v/icloud/af/images/find-my/icon_find_my__dbzk8xw06y6a_large.jpg"))