$fn=50;

lcd_x = 183;
lcd_y = 141;
lcd_z = 6;

wall_w = 8;
wall_n = 4;
screw = 4;

module lcd() {
    color([0,0.5,0,0.5]) cube([lcd_x, lcd_y, lcd_z]);
}

module short(z = lcd_z) {
    cube([wall_w, lcd_y+wall_w, z]);
}

module long(z = lcd_z) {
    cube([lcd_x+wall_w, wall_w, z]);
}

module screwhole(z = lcd_z) {
    cylinder(d1=screw,d2=screw,h=z);
}

module screw() {
    cube([wall_w,wall_w,wall_w]);
}

module mount() {
  difference() {
    union() {
    difference() {
        translate([0, lcd_y, 0]) long(wall_n);
        translate([wall_w/2, wall_w/2+lcd_y, 0]) screwhole(wall_n);
    }
    difference() {
        translate([lcd_x, 0, 0]) short(wall_n);
        translate([wall_w/2+lcd_x, wall_w/2, 0]) screwhole(wall_n);
    }
    difference() {
        short(wall_n);
        translate([wall_w/2, wall_w/2+lcd_y, 0]) screwhole(wall_n);
        translate([wall_w/2, wall_w/2, 0]) screwhole(wall_n);
    }
    translate([2*wall_w,lcd_y,0]) screw();
    translate([lcd_x-2*wall_w,lcd_y,0]) screw();
    translate([lcd_x,lcd_y-2*wall_w,0]) screw();
    translate([lcd_x,2*wall_w,0]) screw();
    }
    translate([wall_w+lcd_x,wall_w/2+2*wall_w,wall_w/2]) rotate([0,-90,0]) screwhole(wall_w);
    translate([wall_w+lcd_x,wall_w/2+lcd_y-2*wall_w,wall_w/2]) rotate([0,-90,0]) screwhole(wall_w);
    translate([2*wall_w+wall_w/2,lcd_y+wall_w,wall_w/2]) rotate([90,0,0]) screwhole(wall_w);
    translate([lcd_x-wall_w-wall_w/2,lcd_y+wall_w,wall_w/2]) rotate([90,0,0]) screwhole(wall_w);
  }
}

module holder() {
    difference() {
        long(lcd_z);
        translate([wall_w/2+lcd_x, wall_w/2, 0]) screwhole(lcd_z);
        translate([wall_w/2, wall_w/2, 0]) screwhole(lcd_z);
    }
    difference() {
        short(lcd_z);
        translate([wall_w/2, wall_w/2+lcd_y, 0]) screwhole(lcd_z);
        translate([wall_w/2, wall_w/2, 0]) screwhole(lcd_z);
    }
}

translate([2*wall_w,0,0]) holder();
translate([0,2*wall_w,0]) mount();

//translate([wall_w,wall_w,0]) lcd();