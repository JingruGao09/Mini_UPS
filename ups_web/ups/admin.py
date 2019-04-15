from django.contrib import admin
from ups.models import World, UpsProfile, Truck, Package, Product, Shipment

class WorldAdmin(admin.ModelAdmin):
    list_display = ('world_id','status')
admin.site.register(World,WorldAdmin)

'''
class UpsProfile(admin.ModelAdmin):
    list_display=('user')
'''
class TruckAdmin(admin.ModelAdmin):
    list_display=('world_id','truck_id','wh_id','wh_x','wh_y','truck_status')

admin.site.register(Truck,TruckAdmin)

class PackageAdmin(admin.ModelAdmin):
    list_display=('package_id','user','world','seqnum','truck','des_x','des_y','package_status')

admin.site.register(Package,PackageAdmin)


class ProductAdmin(admin.ModelAdmin):
    list_display=('product_id','package','world','description','count')

admin.site.register(Product,ProductAdmin)


class ShipmentAdmin(admin.ModelAdmin):
    list_display=('ship_id','package','world')

admin.site.register(Shipment,ShipmentAdmin)
