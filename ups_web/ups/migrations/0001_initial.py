# Generated by Django 2.1.5 on 2019-04-18 14:41

from django.conf import settings
from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    initial = True

    dependencies = [
        migrations.swappable_dependency(settings.AUTH_USER_MODEL),
    ]

    operations = [
        migrations.CreateModel(
            name='Package',
            fields=[
                ('package_id', models.IntegerField(primary_key=True, serialize=False)),
                ('des_x', models.IntegerField()),
                ('des_y', models.IntegerField()),
                ('package_status', models.CharField(choices=[('1', 'created'), ('2', 'truck en route to warehouse'), ('3', 'truck waiting for package'), ('4', 'out for delivery'), ('5', 'Delivered')], default='1', help_text='Package Status', max_length=1)),
            ],
            options={
                'db_table': 'package',
            },
        ),
        migrations.CreateModel(
            name='Product',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('product_id', models.BigIntegerField()),
                ('description', models.CharField(default='AProduct', max_length=100)),
                ('count', models.IntegerField(default=1)),
                ('package', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, related_name='package_set', to='ups.Package')),
            ],
            options={
                'db_table': 'product',
            },
        ),
        migrations.CreateModel(
            name='Shipment',
            fields=[
                ('ship_id', models.BigIntegerField(primary_key=True, serialize=False)),
                ('package', models.ForeignKey(on_delete=django.db.models.deletion.DO_NOTHING, to='ups.Package')),
            ],
            options={
                'db_table': 'shipment',
            },
        ),
        migrations.CreateModel(
            name='Truck',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('truck_id', models.IntegerField()),
                ('wh_id', models.IntegerField()),
                ('wh_x', models.IntegerField()),
                ('wh_y', models.IntegerField()),
                ('truck_status', models.CharField(blank=True, choices=[('1', 'idle'), ('2', 'en route to a warehouse'), ('3', 'invalid'), ('4', 'delivering'), ('5', 'waiting for pickup')], default='1', help_text='Truck Status', max_length=1, null=True)),
            ],
            options={
                'db_table': 'truck',
            },
        ),
        migrations.CreateModel(
            name='UpsProfile',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('user', models.OneToOneField(on_delete=django.db.models.deletion.CASCADE, related_name='profile', to=settings.AUTH_USER_MODEL)),
            ],
            options={
                'db_table': 'ups_profile',
            },
        ),
        migrations.CreateModel(
            name='World',
            fields=[
                ('world_id', models.AutoField(primary_key=True, serialize=False)),
                ('status', models.CharField(default='OPEN', max_length=20)),
            ],
            options={
                'db_table': 'world',
            },
        ),
        migrations.AddField(
            model_name='truck',
            name='world',
            field=models.ForeignKey(on_delete=django.db.models.deletion.DO_NOTHING, to='ups.World'),
        ),
        migrations.AddField(
            model_name='shipment',
            name='world',
            field=models.ForeignKey(on_delete=django.db.models.deletion.DO_NOTHING, to='ups.World'),
        ),
        migrations.AddField(
            model_name='product',
            name='world',
            field=models.ForeignKey(on_delete=django.db.models.deletion.DO_NOTHING, to='ups.World'),
        ),
        migrations.AddField(
            model_name='package',
            name='truck',
            field=models.ForeignKey(on_delete=django.db.models.deletion.DO_NOTHING, to='ups.Truck'),
        ),
        migrations.AddField(
            model_name='package',
            name='user',
            field=models.ForeignKey(blank=True, null=True, on_delete=django.db.models.deletion.CASCADE, related_name='user_set', to='ups.UpsProfile'),
        ),
        migrations.AddField(
            model_name='package',
            name='world',
            field=models.ForeignKey(on_delete=django.db.models.deletion.DO_NOTHING, to='ups.World'),
        ),
    ]
