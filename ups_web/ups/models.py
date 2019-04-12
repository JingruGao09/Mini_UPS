# This is an auto-generated Django model module.
# You'll have to do the following manually to clean this up:
#   * Rearrange models' order
#   * Make sure each model has one field with primary_key=True
#   * Make sure each ForeignKey has `on_delete` set to the desired behavior.
#   * Remove `managed = False` lines if you wish to allow Django to create, modify, and delete the table
# Feel free to rename the models, but don't rename db_table values or field names.
from django.db import models
from django.contrib.auth.models import User

class World(models.Model):
    world_id = models.AutoField(primary_key=True)

    class Meta:
        db_table = 'world'

    def __str__(self):
        return world_id

class UpsProfile(models.Model):
    user = models.OneToOneField(User,on_delete=models.CASCADE, unique=True)

    class Meta:
        db_table = 'ups_profile'

    def __str__(self):
        return self.user.__str__()

class Truck(models.Model):
    #package = models.ForeignKey(Package, models.DO_NOTHING, primary_key=True)
    world = models.ForeignKey('World', models.DO_NOTHING)
    truck_id = models.IntegerField(null = False)
    TRUCK_STATUS_OP = (
        ('1','idle'),
        ('2','en route to a warehouse'),
        ('3','invalid'),
        ('4','delivering'),
        ('5','waiting for pickup')
    )

    truck_status = models.CharField(max_length=1,
                                    choices = TRUCK_STATUS_OP,
                                    blank = True,
                                    default = '5',
                                    null = True,
                                    help_text='Truck Status')
    class Meta:
        db_table = 'truck'

    def __str__(self):
        return self.truck_id

class Package(models.Model):
    package_id = models.IntegerField(primary_key=True)
    user = models.ForeignKey('UpsProfile', models.DO_NOTHING)
    world = models.ForeignKey('World', models.DO_NOTHING)
    seqnum = models.IntegerField(null = False)
    truck = models.ForeignKey('Truck',models.DO_NOTHING)
    x = models.IntegerField()
    y = models.IntegerField()

    class Meta:
        db_table = 'package'

    def __str__(self):
        return package_id


class Shipment(models.Model):
    ship_id = models.AutoField(primary_key=True)
    package = models.ForeignKey(Package, models.DO_NOTHING)
    world = models.ForeignKey('World', models.DO_NOTHING)
    #packing, packed, loading, loaded, delivering, delivered
    #status = models.CharField(max_length=50)

    class Meta:
        db_table = 'shipment'

    def __str__(self):
        return ship_id


