// sidewinder vyska (spodni)
sidewinder_height = 28.5; // 29.2mm
//sidewinder_height = 10;
// vyska mezikusu
inter_height = 3;

// sirka steny
wall = 2.3; // 2.3mm (CH FS)
fs_wall = 2.3;
sd_wall = wall;

// sidewinder
sidewinder_diameter = 14.5; // 13.9mm
cube_width = 6; // 5.6mm

// fighterstick
fighterstick_diameter = 12.4; // 12.6mm
fighterstick_height = 39.6; // 39.6mm
fighterstick_rotation = 10;
stable_length = 14.8; // 15mm
stable_width = 2.0; // 2.3mm
//fighterstick_height = 4; // 39.6mm

// inter
idr = (sidewinder_diameter + 2 * wall) / 2;
iur = stable_length / 2;

adapter(sidewinder_height,inter_height,fighterstick_height);

module adapter(s,z,f) {
    rotate([0,0,fighterstick_rotation]) { translate([0,0,s+z]) { fighterstick(f,8); } }
    translate([0,0,s]) { interpart(z,idr,iur); }
    sidewinder(s);
}

module interpart(height,d,u) {
    holer = fighterstick_diameter - 2 * fs_wall;
    difference() {
        union() {
            translate([0,0,height*0.5]) { cylinder(height*0.5,d,u); }
            cylinder(height*0.5,r=d);
        }
        cylinder(height,sidewinder_diameter/2,holer/2);
    }
}

module sidewinder(height) {
  diameter = sidewinder_diameter;
  outer_diameter = diameter + 2 * wall;
  cubew = cube_width;
  union() {
    difference() {
      cylinder(height,d=outer_diameter);
      cylinder(height,diameter/2,(diameter/2));
    }
    intersection() {
      translate([0,cubew,height+inter_height-((cubew+inter_height)/2)]) { 
        translate([0,1.45,-1.45]) {
          union() {
            sphere(d=cubew+0.5,true);
            cylinder(cubew+0.5,d=cubew+0.5,true);
          }
        }
      }
      union() {
        cylinder(height+inter_height,d=fighterstick_diameter-2*wall);
        translate([0,0,sidewinder_height+inter_height/2]) {
          cylinder(inter_height/2,idr,iur);
        }
        cylinder(sidewinder_height+inter_height/2,d=sidewinder_diameter+2*wall);      
      }
    }
  }
}

module fighterstick(height) {
    diameter = fighterstick_diameter;
    stablel = stable_length;
    stablew = stable_width;
    wall = fs_wall;
    hole_diameter = 2.3; // 2.3mm (depth = 2.2mm)
    hole_height = 12.85; // 11.7mm
    difference() {
        union() {
            cylinder(height,d=diameter);
            translate([0,0,height/2]) { cube([stablew,stablel,height],true); }
        }
        cylinder(height,d=diameter-2*wall);
        translate([-diameter/2-0.5,0,hole_height]) {
            rotate([0,90,0]) { sphere(d=hole_diameter, true); }
        }
        translate([diameter/2+0.5,0,hole_height]) {
            rotate([0,90,0]) { sphere(d=hole_diameter, true); }
        }

   }
}
