
import json
 
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
    "link": "https://aiwize.com/",
    "icon": "aiwize://resources/brave-icons/product-brave-leo.svg"
}
apps.append(app)

for item in items:
    title = item.get("name", None)
    link = item.get('website', None)
    description = item.get('description', title)
    categories = item.get("category", [])
    if not title:
       print(f"Warning! {item}")
       exit
    if link:
      app = {
          "id": item["id"],
          "title": title,
          "description": description,
          "categories" : categories,
          "link": link
      }
      apps.append(app)

result["items"] = apps

print(result)
with open("apps.json", "w") as jsonFile:
    jsonFile.write(json.dumps(result))
