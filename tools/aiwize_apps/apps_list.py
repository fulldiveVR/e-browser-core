
import json
import favicon

result = {}
 
with open("apps_list.json", "r") as jsonFile:
    apps_data = json.loads(jsonFile.read())

result["categories"] = apps_data["categories"]
items = apps_data["appPresets"]
apps = []
app = {
    "id": "aiwize",
    "title": "AI Wize",
    "description": "AI Wize",
    "categories" : ["ai", "popular"],
    "link": "https://aiwize.com/"
}
apps.append(app)

def sortIcons(item):
   return item.width * item.height

def filterIcons(item):
   return item.format == 'png'

def fetchFavIcons(link: str) -> list:
   print(f"fetchFavIcons: {link}")
   if "adobe.com" in link or "marketo.com" in link:
    return ["https://business.adobe.com/img/favicons/favicon-180.png"]

   if "www.tokopedia.com" in link:
    return []

   try:
    icons = favicon.get(url=link)
    icons = list(filter(filterIcons, icons))
    icons.sort(reverse=True, key=sortIcons)
    print(icons)
    return list(map(lambda x:x.url, icons))
   except Exception as ex:
        print(ex)

   return []

for item in items:
    title = item.get("name", None)
    link = item.get('website', None)
    description = item.get('description', title)
    categories = item.get("category", [])
    if not title:
       print(f"Warning! {item}")
       exit
    if link:
      icons = fetchFavIcons(link)
      icon = None
      if len(icons) > 0: 
          icon = icons[0]
      print(f"{title} - {icon}")
      app = {
          "id": item["id"],
          "title": title,
          "description": description,
          "categories" : categories,
          "link": link,
          "icon": icon,
          "icons": icons
      }
      apps.append(app)

      result["items"] = apps

      with open("apps.json", "w") as jsonFile:
        jsonFile.write(json.dumps(result, indent=2))
