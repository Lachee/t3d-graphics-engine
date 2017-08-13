# Required Blender information.
bl_info = {
           "name": "T3D Raw Exporter",
           "author": "Lachlan Hopkins",
           "version": (4, 0),
           "blender": (2, 65, 0),
           "location": "File > Export > T3D (.t3dmesh)",
           "description": "Generates a text file with raw vertex index + position and a triangle index map. Designed for simplifed import into the T3D game engine, for best results, keep the meshes simple and use quads or triangles only.",
           "warning": "",
           "wiki_url": "http://graphicsandgames.com",
           "tracker_url": "https://github.com/Lachee/t3d-graphics-engine/issues",
           "category": "Import-Export"
          }

import bpy


def write_data(context, filepath, data):
    print("running write_some_data...")
    f = open(filepath, 'w', encoding='utf-8')
    f.write(data)
    f.close()

    return {'FINISHED'}

def triangulate(face):
    triangles = []
    if len(face) == 4:
        triangles.append([face[0], face[1], face[2]])
        triangles.append([face[2], face[3], face[0]])
    else:
        triangles.append(face)

    return triangles

def calculateFaces(face, mesh, matrix):
    fv = []
    for verti in face.vertices:
        fv.append((matrix * mesh.vertices[verti].co)[:])
    return fv

def rotate(obj, co, rotation) :
    # define the rotation
    rot_mat_x = Matrix.Rotation(radians(rotation[0]), 4, 'X')   # you can also use as axis Y,Z or a custom vector like (x,y,z)
    rot_mat_y = Matrix.Rotation(radians(rotation[1]), 4, 'Y')   # you can also use as axis Y,Z or a custom vector like (x,y,z)
    rot_mat_z = Matrix.Rotation(radians(rotation[2]), 4, 'Z')   # you can also use as axis Y,Z or a custom vector like (x,y,z)

    # decompose world_matrix's components, and from them assemble 4x4 matrices
    orig_loc, orig_rot, orig_scale = obj.matrix_world.decompose()
    orig_loc_mat = Matrix.Translation(orig_loc)
    orig_rot_mat = orig_rot.to_matrix().to_4x4()
    orig_scale_mat = Matrix.Scale(orig_scale[0],4,(1,0,0)) * Matrix.Scale(orig_scale[1],4,(0,1,0)) * Matrix.Scale(orig_scale[2],4,(0,0,1))
    
    return  co * orig_loc_mat * rot_mat_z * rot_mat_y * rot_mat_x * orig_rot_mat * orig_scale_mat;
    
# ExportHelper is a helper class, defines filename and
# invoke() function which calls the file selector.
from bpy_extras.io_utils import ExportHelper
from bpy.props import StringProperty, BoolProperty, EnumProperty, FloatVectorProperty
from bpy.types import Operator
from math import radians
from mathutils import Matrix

class ExportT3D(Operator, ExportHelper):
    """This appears in the tooltip of the operator and in the generated docs"""
    bl_idname = "export_t3d.data"  # important since its how bpy.ops.import_test.some_data is constructed
    bl_label = "Export T3D Data"

    # ExportHelper mixin class uses this
    filename_ext = ".t3dmesh"

    filter_glob = StringProperty(
            default="*.t3dmesh",
            options={'HIDDEN'},
            maxlen=255,  # Max internal buffer length, longer would be clamped.
            )

    # List of operator properties, the attributes will be assigned
    # to the class instance from the operator settings before calling.
    apply_modifiers = BoolProperty(
            name="Apply Modifiers",
            description="When exporting, should we apply the modifiers to the mesh",
            default=True,
            )    
            
    model_rotation = FloatVectorProperty(
        name="Rotation",
        description="When exporting, should we apply the modifiers to the mesh",
		subtype="XYZ",
        default=(-90, 180, 180),
        )

    def execute(self, context):
        mesh = None        
        is_tmp_mesh = False
        scene = bpy.context.scene
        filename = self.filepath;
        filecount = 0;
            
        for obj in bpy.context.selected_objects:
            print("Saving " + obj.name + " to " + filename);
                    
            if self.apply_modifiers or obj.type != 'MESH':
                try:
                    mesh = obj.to_mesh(scene, True, "PREVIEW")
                except:
                    mesh = None
                    is_tmp_mesh = True
            else:
                mesh = obj.data
                if not mesh.tessfaces and mesh.polygons:
                    mesh.calc_tessface()
                is_tmp_mesh = False

            if mesh is not None:
                line = "";
                
                vertices = [];
                triangles = [];
                #matrix = obj.matrix_world.copy()             
                #for face in mesh.tessfaces:
                #    fv = calculateFaces(face, mesh, matrix)
                #    faces = triangulate(fv);
                #    print(fv);
                #    print(faces);
                
                for v in mesh.vertices:
                    pos = rotate(obj, v.co, self.model_rotation);
                    vertices.append([v.index, pos[0], pos[1], pos[2]]);
                
                for f in mesh.tessfaces:
                    if (len(f.vertices) >= 3):
                        triangles.extend([f.vertices[0], f.vertices[1], f.vertices[2]])
                        
                    if (len(f.vertices) == 4):   
                        triangles.extend([f.vertices[2], f.vertices[3], f.vertices[0]])
                
                line += "vertices: " + str(len(vertices)) + "\n";                
                line += "triangles: " + str(len(triangles)  // 3) + "\n";
                
                for v in vertices:
                    line += str(v[0])+":"+str(v[1])+","+str(v[2])+","+str(v[3])+"\n"
                    
                tricount = 0;
                for t in triangles:
                    if tricount > 0:
                        if tricount % 3 == 0:
                            line += "\n"
                        else:
                           line += ","
                        
                    line += str(t);
                    tricount += 1;
                
                if is_tmp_mesh:
                    bpy.data.meshes.remove(mesh)
                
                if filecount > 0:
                    filename += self.filepath + "." + str(filecount);
                filecount += 1;
                
                write_data(context, filename, line);
                
        return {'FINISHED'}
        #return write_data(context, self.filepath, "test")
      

# Only needed if you want to add into a dynamic menu
def menu_func_export(self, context):
    self.layout.operator(ExportT3D.bl_idname, text="T3D Raw (.t3dmesh)")


def register():
    bpy.utils.register_class(ExportT3D)
    bpy.types.INFO_MT_file_export.append(menu_func_export)


def unregister():
    bpy.utils.unregister_class(ExportT3D)
    bpy.types.INFO_MT_file_export.remove(menu_func_export)


if __name__ == "__main__":
    register()
    #
    # test call
    bpy.ops.export_t3d.data('INVOKE_DEFAULT'); 
    #unregister();
