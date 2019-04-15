from django.contrib import admin
from ups.models import World, UpsProfile, Truck, Package, Shipment

class WorldAdmin(admin.ModelAdmin):
    list_display = ('world_id','status')
admin.site.register(World,WorldAdmin)

'''
class UpsProfile(admin.ModelAdmin):
    list_display=('user')
'''
class TruckAdmin(admin.ModelAdmin):
    list_display=('world_id','truck_id','truck_status')

admin.site.register(Truck,TruckAdmin)

class PackageAdmin(admin.ModelAdmin):
    list_display=('package_id','user','world','seqnum','truck','x','y')

admin.site.register(Package,PackageAdmin)

class ShipmentAdmin(admin.ModelAdmin):
    list_display=('ship_id','package','world')

admin.site.register(Shipment,ShipmentAdmin)
