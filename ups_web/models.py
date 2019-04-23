# This is an auto-generated Django model module.
# You'll have to do the following manually to clean this up:
#   * Rearrange models' order
#   * Make sure each model has one field with primary_key=True
#   * Make sure each ForeignKey has `on_delete` set to the desired behavior.
#   * Remove `managed = False` lines if you wish to allow Django to create, modify, and delete the table
# Feel free to rename the models, but don't rename db_table values or field names.
from django.db import models


class Ainseqnum(models.Model):
    id = models.BigIntegerField(primary_key=True)

    class Meta:
        managed = False
        db_table = 'ainseqnum'


class Aoutseqnum(models.Model):
    id = models.BigAutoField(primary_key=True)
    msg = models.CharField(max_length=65535, blank=True, null=True)
    time = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'aoutseqnum'


class Inseqnum(models.Model):
    id = models.BigIntegerField(primary_key=True)
    world = models.ForeignKey('World', models.DO_NOTHING)

    class Meta:
        managed = False
        db_table = 'inseqnum'
        unique_together = (('id', 'world'),)


class Outseqnum(models.Model):
    id = models.BigAutoField(primary_key=True)
    type = models.IntegerField(blank=True, null=True)
    truck_id = models.IntegerField(blank=True, null=True)
    wh_id = models.IntegerField(blank=True, null=True)
    package_id = models.IntegerField(blank=True, null=True)
    package_x = models.IntegerField(blank=True, null=True)
    package_y = models.IntegerField(blank=True, null=True)
    world = models.ForeignKey('World', models.DO_NOTHING)
    time = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'outseqnum'
        unique_together = (('id', 'world'),)


class Package(models.Model):
    package_id = models.BigIntegerField(primary_key=True)
    world = models.ForeignKey('World', models.DO_NOTHING)
    truck_id = models.IntegerField(blank=True, null=True)
    user_id = models.IntegerField(blank=True, null=True)
    package_status = models.CharField(max_length=50)
    dep_x = models.IntegerField()
    dep_y = models.IntegerField()
    des_x = models.IntegerField()
    des_y = models.IntegerField()
    descp = models.TextField(blank=True, null=True)
    count = models.IntegerField(blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'package'
        unique_together = (('package_id', 'world'),)


class Truck(models.Model):
    truck_id = models.IntegerField(primary_key=True)
    x = models.IntegerField()
    y = models.IntegerField()
    world = models.ForeignKey('World', models.DO_NOTHING)
    truck_status = models.CharField(max_length=50)

    class Meta:
        managed = False
        db_table = 'truck'
        unique_together = (('truck_id', 'world'),)


class World(models.Model):
    world_id = models.IntegerField(primary_key=True)
    status = models.CharField(max_length=10)

    class Meta:
        managed = False
        db_table = 'world'
