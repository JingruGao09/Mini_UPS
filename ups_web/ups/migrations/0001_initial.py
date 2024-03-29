
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
                ('package_id', models.BigIntegerField(primary_key=True, serialize=False)),
                ('user_id', models.IntegerField(null=True)),
                ('world_id', models.IntegerField()),
                ('dep_x', models.IntegerField(help_text='Depature x')),
                ('dep_y', models.IntegerField(help_text='Depature y')),
                ('des_x', models.IntegerField(help_text='Destination x')),
                ('des_y', models.IntegerField(help_text='Destination y')),
                ('descp', models.TextField(null=True)),
                ('count', models.IntegerField(null=True)),
                ('package_status', models.CharField(choices=[('CREATED', 'CREATED'), ('TRUCK EN ROUTE TO WAREHOUSE', 'TRUCK EN ROUTE TO WAREHOUSE'), ('TRUCK WAITING FOR PACKAGE', 'TRUCK WAITING FOR PACKAGE'), ('OUT FOR DELIVERY', 'OUT FOR DELIVERY'), ('DELIVERED', 'DELIVERED')], default='CREATED', help_text='Package Status', max_length=50)),
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
            name='Shiplog',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('packagelog', models.TextField()),
                ('package', models.ForeignKey(on_delete=django.db.models.deletion.DO_NOTHING, to='ups.Package')),
            ],
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
                ('world_id', models.IntegerField()),
                ('truck_id', models.IntegerField(primary_key=True, serialize=False)),
                ('x', models.IntegerField()),
                ('y', models.IntegerField()),
                ('truck_status', models.CharField(choices=[('IDLE', 'IDLE'), ('EN ROUTE TO A WAREHOUSE', 'EN ROUTE TO A WAREHOUSE'), ('ARRIVED WAREHOUSE', 'ARRIVED WAREHOUSE'), ('DELIVERING', 'DELIVERING'), ('WAITING FOR PICKUP', 'WAITING FOR PICKUP'), ('INVAILD', 'INVAILD')], default='IDLE', help_text='Truck Status', max_length=50, null=True)),
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
                ('speed', models.IntegerField(null=True)),
            ],
            options={
                'db_table': 'world',
            },
        ),
        migrations.AddField(
            model_name='shipment',
            name='world',
            field=models.ForeignKey(on_delete=django.db.models.deletion.DO_NOTHING, to='ups.World'),
        ),
        migrations.AddField(
            model_name='shiplog',
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
            field=models.ForeignKey(null=True, on_delete=django.db.models.deletion.DO_NOTHING, to='ups.Truck'),
        ),
    ]
