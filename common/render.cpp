extern "C"
{
#include <raylib.h>
}
#include <render.h>
#include <string>

void NullLog(int logLevel, const char *text, va_list args) {}

Camera SetupCamera(Point camera_position)
{
  Camera camera = { 0 };
  camera.position = (Vector3){ camera_position.x, camera_position.y, camera_position.z };
  camera.target = (Vector3){ 0.0f, 1.0f, 0.0f };
  camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
  camera.fovy = 45.0f;
  camera.projection = CAMERA_PERSPECTIVE;

  return camera;
}

void DrawModelToTexture(RenderTexture target, Model model, Point camera_position)
{
  Camera camera = SetupCamera(camera_position);
  Vector3 position = { 0.0f, 0.0f, 0.0f };

  BeginTextureMode(target);
  ClearBackground(RAYWHITE);
  BeginMode3D(camera);
  DrawModel(model, position, 0.1f, WHITE);
  DrawGrid(10, 1.0f);
  EndMode3D();
  EndTextureMode();
}

void DrawRenderTextureWithShader(RenderTexture target, Shader shader)
{
  BeginDrawing();
  ClearBackground(RAYWHITE);
  BeginShaderMode(shader);
  DrawTextureRec(target.texture, (Rectangle){ 0, 0, (float)target.texture.width, (float)-target.texture.height }, (Vector2){ 0, 0 }, WHITE);
  EndShaderMode();
  EndDrawing();
}

static Model model;
static RenderTexture2D target;
static Texture2D texture;
static Shader shader;

void RenderWithShader(const std::string& path, Point camera_position)
{
  SetTraceLogCallback(NullLog);
  SetConfigFlags(FLAG_OFFSCREEN_MODE);
  InitWindow(800, 600, "");

  model = LoadModel("assets/church.obj");
  texture = LoadTexture("assets/church_diffuse.png");
  model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

  shader = LoadShader(nullptr, path.c_str());
  target = LoadRenderTexture(800, 600);

  DrawModelToTexture(target, model, camera_position);
  DrawRenderTextureWithShader(target, shader);
}

void CleanUp()
{
  UnloadTexture(texture);
  UnloadModel(model);
  UnloadRenderTexture(target);
  UnloadShader(shader);
  CloseWindow();
}
