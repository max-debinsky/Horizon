#include "horizon/camera.h"
#include "horizon/utility.h"
#include <cmath>

Camera::Camera(point3 lookfrom, point3 lookat, vector3 vup, double vfov, double aspect_ratio, double defocus_angle, double focus_dist) {
    lens_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));

    double theta = degrees_to_radians(vfov);
    double h = std::tan(theta / 2);
    double viewport_height = 2.0 * h * focus_dist;
    double viewport_width = aspect_ratio * viewport_height;

    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);

    origin = lookfrom;
    horizontal = viewport_width * u;
    vertical = viewport_height * v; // downwards in image
    lower_left_corner = origin - horizontal/2 - vertical/2 - focus_dist * w;
}

ray Camera::get_ray(double s, double t) const {
    vector3 rd = lens_radius > 0 ? random_in_unit_disk() : vector3(0,0,0);
    vector3 offset = u * rd.x + v * rd.y;
    return ray(origin + offset, lower_left_corner + s*horizontal + t*vertical - origin - offset);
}
