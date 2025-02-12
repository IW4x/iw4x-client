#pragma once

#define PROTOCOL 0x98
#define NUM_CUSTOM_CLASSES 15
#define FX_ELEM_FIELD_COUNT 90

#define MAX_QPATH 64
#define MAX_OSPATH 256

// This allows us to compile our structures in IDA, for easier reversing :3
#ifndef __cplusplus
#define IDA
#endif

#ifndef IDA
namespace Game
{
#endif
	constexpr std::size_t MAX_GENTITIES = 2048;
	constexpr std::size_t ENTITYNUM_NONE = MAX_GENTITIES - 1;

	typedef float vec_t;
	typedef vec_t vec2_t[2];
	typedef vec_t vec3_t[3];
	typedef vec_t vec4_t[4];

	typedef unsigned __int16 scr_string_t;

	struct scr_entref_t
	{
		unsigned __int16 entnum;
		unsigned __int16 classnum;
	};

	typedef void(*BuiltinFunction)();
	typedef void(*BuiltinMethod)(scr_entref_t);

	struct BuiltinFunctionDef
	{
		const char* actionString;
		BuiltinFunction actionFunc;
		int type;
	};

	struct BuiltinMethodDef
	{
		const char* actionString;
		BuiltinMethod actionFunc;
		int type;
	};

	enum XAssetType
	{
		ASSET_TYPE_PHYSPRESET = 0x0,
		ASSET_TYPE_PHYSCOLLMAP = 0x1,
		ASSET_TYPE_XANIMPARTS = 0x2,
		ASSET_TYPE_XMODEL_SURFS = 0x3,
		ASSET_TYPE_XMODEL = 0x4,
		ASSET_TYPE_MATERIAL = 0x5,
		ASSET_TYPE_PIXELSHADER = 0x6,
		ASSET_TYPE_VERTEXSHADER = 0x7,
		ASSET_TYPE_VERTEXDECL = 0x8,
		ASSET_TYPE_TECHNIQUE_SET = 0x9,
		ASSET_TYPE_IMAGE = 0xA,
		ASSET_TYPE_SOUND = 0xB,
		ASSET_TYPE_SOUND_CURVE = 0xC,
		ASSET_TYPE_LOADED_SOUND = 0xD,
		ASSET_TYPE_CLIPMAP_SP = 0xE,
		ASSET_TYPE_CLIPMAP_MP = 0xF,
		ASSET_TYPE_COMWORLD = 0x10,
		ASSET_TYPE_GAMEWORLD_SP = 0x11,
		ASSET_TYPE_GAMEWORLD_MP = 0x12,
		ASSET_TYPE_MAP_ENTS = 0x13,
		ASSET_TYPE_FXWORLD = 0x14,
		ASSET_TYPE_GFXWORLD = 0x15,
		ASSET_TYPE_LIGHT_DEF = 0x16,
		ASSET_TYPE_UI_MAP = 0x17,
		ASSET_TYPE_FONT = 0x18,
		ASSET_TYPE_MENULIST = 0x19,
		ASSET_TYPE_MENU = 0x1A,
		ASSET_TYPE_LOCALIZE_ENTRY = 0x1B,
		ASSET_TYPE_WEAPON = 0x1C,
		ASSET_TYPE_SNDDRIVER_GLOBALS = 0x1D,
		ASSET_TYPE_FX = 0x1E,
		ASSET_TYPE_IMPACT_FX = 0x1F,
		ASSET_TYPE_AITYPE = 0x20,
		ASSET_TYPE_MPTYPE = 0x21,
		ASSET_TYPE_CHARACTER = 0x22,
		ASSET_TYPE_XMODELALIAS = 0x23,
		ASSET_TYPE_RAWFILE = 0x24,
		ASSET_TYPE_STRINGTABLE = 0x25,
		ASSET_TYPE_LEADERBOARD = 0x26,
		ASSET_TYPE_STRUCTURED_DATA_DEF = 0x27,
		ASSET_TYPE_TRACER = 0x28,
		ASSET_TYPE_VEHICLE = 0x29,
		ASSET_TYPE_ADDON_MAP_ENTS = 0x2A,
		ASSET_TYPE_COUNT = 0x2B,
		ASSET_TYPE_STRING = 0x2B,
		ASSET_TYPE_ASSETLIST = 0x2C,
		ASSET_TYPE_INVALID = -1,
	};

	enum GfxWarningType
	{
		R_WARN_FRONTEND_ENT_LIMIT = 0x0,
		R_WARN_KNOWN_MODELS = 0x1,
		R_WARN_KNOWN_PER_CLIENT_MODELS = 0x2,
		R_WARN_KNOWN_SPECIAL_MODELS = 0x3,
		R_WARN_MODEL_LIGHT_CACHE = 0x4,
		R_WARN_SCENE_ENTITIES = 0x5,
		R_WARN_TEMP_SKIN_BUF_SIZE = 0x6,
		R_WARN_MAX_SKINNED_CACHE_VERTICES = 0x7,
		R_WARN_MAX_SCENE_SURFS_SIZE = 0x8,
		R_WARN_MAX_SURF_BUF = 0x9,
		R_WARN_PORTAL_PLANES = 0xA,
		R_WARN_MAX_CLOUDS = 0xB,
		R_WARN_MAX_DLIGHTS = 0xC,
		R_WARN_SMODEL_LIGHTING = 0xD,
		R_WARN_SMODEL_VIS_DATA_LIMIT = 0xE,
		R_WARN_SMODEL_SURF_LIMIT = 0xF,
		R_WARN_SMODEL_SURF_DELAY_LIMIT = 0x10,
		R_WARN_BSPSURF_DATA_LIMIT = 0x11,
		R_WARN_BSPSURF_PRETESS_LIMIT = 0x12,
		R_WARN_MAX_DRAWSURFS = 0x13,
		R_WARN_GFX_CODE_EMISSIVE_SURF_LIMIT = 0x14,
		R_WARN_GFX_CODE_TRANS_SURF_LIMIT = 0x15,
		R_WARN_GFX_GLASS_SURF_LIMIT = 0x16,
		R_WARN_GFX_MARK_SURF_LIMIT = 0x17,
		R_WARN_GFX_SPARK_SURF_LIMIT = 0x18,
		R_WARN_MAX_SCENE_DRAWSURFS = 0x19,
		R_WARN_MAX_FX_DRAWSURFS = 0x1A,
		R_WARN_NONEMISSIVE_FX_MATERIAL = 0x1B,
		R_WARN_NONLIT_MARK_MATERIAL = 0x1C,
		R_WARN_CMDBUF_OVERFLOW = 0x1D,
		R_WARN_MISSING_DECL_NONDEBUG = 0x1E,
		R_WARN_MAX_DYNENT_REFS = 0x1F,
		R_WARN_MAX_SCENE_DOBJ_REFS = 0x20,
		R_WARN_MAX_SCENE_MODEL_REFS = 0x21,
		R_WARN_MAX_SCENE_BRUSH_REFS = 0x22,
		R_WARN_MAX_CODE_EMISSIVE_INDS = 0x23,
		R_WARN_MAX_CODE_EMISSIVE_VERTS = 0x24,
		R_WARN_MAX_CODE_EMISSIVE_ARGS = 0x25,
		R_WARN_MAX_CODE_TRANS_INDS = 0x26,
		R_WARN_MAX_CODE_TRANS_VERTS = 0x27,
		R_WARN_MAX_CODE_TRANS_ARGS = 0x28,
		R_WARN_MAX_GLASS_INDS = 0x29,
		R_WARN_MAX_GLASS_VERTS = 0x2A,
		R_WARN_MAX_MARK_INDS = 0x2B,
		R_WARN_MAX_MARK_VERTS = 0x2C,
		R_WARN_MAX_SPARK_INDS = 0x2D,
		R_WARN_MAX_SPARK_VERTS = 0x2E,
		R_WARN_DEBUG_ALLOC = 0x2F,
		R_WARN_SPOT_LIGHT_LIMIT = 0x30,
		R_WARN_FX_ELEM_LIMIT = 0x31,
		R_WARN_FX_BOLT_LIMIT = 0x32,
		R_WARN_WORKER_CMD_SIZE = 0x33,
		R_WARN_UNKNOWN_STATICMODEL_SHADER = 0x34,
		R_WARN_UNKNOWN_XMODEL_SHADER = 0x35,
		R_WARN_DYNAMIC_INDEX_BUFFER_SIZE = 0x36,
		R_WARN_TOO_MANY_LIGHT_GRID_POINTS = 0x37,
		R_WARN_FOGABLE_2DTEXT = 0x38,
		R_WARN_FOGABLE_2DGLYPH = 0x39,
		R_WARN_SUN_QUERY = 0x3A,
		R_WARN_ESTIMATED_BOUNDS_TOO_SMALL = 0x3B,
		R_WARN_COUNT = 0x3C,
	};

	enum surfType_t
	{
		R_SMODEL_SURFTYPE_RIGID = 0x0,
		R_SMODEL_SURFTYPE_SKINNED = 0x1,
		R_SMODEL_SURFTYPE_CACHED = 0x2,
		R_SMODEL_SURFTYPE_PRETESS = 0x3,
		R_SMODEL_SURFTYPE_COUNT = 0x4,
	};

	enum ShaderCodeConstants
	{
		CONST_SRC_CODE_MAYBE_DIRTY_PS_BEGIN = 0x0,
		CONST_SRC_CODE_LIGHT_POSITION = 0x0,
		CONST_SRC_CODE_LIGHT_DIFFUSE = 0x1,
		CONST_SRC_CODE_LIGHT_SPECULAR = 0x2,
		CONST_SRC_CODE_LIGHT_SPOTDIR = 0x3,
		CONST_SRC_CODE_LIGHT_SPOTFACTORS = 0x4,
		CONST_SRC_CODE_LIGHT_FALLOFF_PLACEMENT = 0x5,
		CONST_SRC_CODE_PARTICLE_CLOUD_COLOR = 0x6,
		CONST_SRC_CODE_GAMETIME = 0x7,
		CONST_SRC_CODE_MAYBE_DIRTY_PS_END = 0x8,
		CONST_SRC_CODE_ALWAYS_DIRTY_PS_BEGIN = 0x8,
		CONST_SRC_CODE_PIXEL_COST_FRACS = 0x8,
		CONST_SRC_CODE_PIXEL_COST_DECODE = 0x9,
		CONST_SRC_CODE_FILTER_TAP_0 = 0xA,
		CONST_SRC_CODE_FILTER_TAP_1 = 0xB,
		CONST_SRC_CODE_FILTER_TAP_2 = 0xC,
		CONST_SRC_CODE_FILTER_TAP_3 = 0xD,
		CONST_SRC_CODE_FILTER_TAP_4 = 0xE,
		CONST_SRC_CODE_FILTER_TAP_5 = 0xF,
		CONST_SRC_CODE_FILTER_TAP_6 = 0x10,
		CONST_SRC_CODE_FILTER_TAP_7 = 0x11,
		CONST_SRC_CODE_COLOR_MATRIX_R = 0x12,
		CONST_SRC_CODE_COLOR_MATRIX_G = 0x13,
		CONST_SRC_CODE_COLOR_MATRIX_B = 0x14,
		CONST_SRC_CODE_SHADOWMAP_POLYGON_OFFSET = 0x15,
		CONST_SRC_CODE_RENDER_TARGET_SIZE = 0x16,
		CONST_SRC_CODE_ALWAYS_DIRTY_PS_END = 0x17,
		CONST_SRC_CODE_FIXED_PS_BEGIN = 0x17,
		CONST_SRC_CODE_DOF_EQUATION_VIEWMODEL_AND_FAR_BLUR = 0x17,
		CONST_SRC_CODE_DOF_EQUATION_SCENE = 0x18,
		CONST_SRC_CODE_DOF_LERP_SCALE = 0x19,
		CONST_SRC_CODE_DOF_LERP_BIAS = 0x1A,
		CONST_SRC_CODE_DOF_ROW_DELTA = 0x1B,
		CONST_SRC_CODE_MOTION_MATRIX_X = 0x1C,
		CONST_SRC_CODE_MOTION_MATRIX_Y = 0x1D,
		CONST_SRC_CODE_MOTION_MATRIX_W = 0x1E,
		CONST_SRC_CODE_SHADOWMAP_SWITCH_PARTITION = 0x1F,
		CONST_SRC_CODE_SHADOWMAP_SCALE = 0x20,
		CONST_SRC_CODE_ZNEAR = 0x21,
		CONST_SRC_CODE_LIGHTING_LOOKUP_SCALE = 0x22,
		CONST_SRC_CODE_DEBUG_BUMPMAP = 0x23,
		CONST_SRC_CODE_MATERIAL_COLOR = 0x24,
		CONST_SRC_CODE_FOG = 0x25,
		CONST_SRC_CODE_FOG_COLOR_LINEAR = 0x26,
		CONST_SRC_CODE_FOG_COLOR_GAMMA = 0x27,
		CONST_SRC_CODE_FOG_SUN_CONSTS = 0x28,
		CONST_SRC_CODE_FOG_SUN_COLOR_LINEAR = 0x29,
		CONST_SRC_CODE_FOG_SUN_COLOR_GAMMA = 0x2A,
		CONST_SRC_CODE_FOG_SUN_DIR = 0x2B,
		CONST_SRC_CODE_GLOW_SETUP = 0x2C,
		CONST_SRC_CODE_GLOW_APPLY = 0x2D,
		CONST_SRC_CODE_COLOR_BIAS = 0x2E,
		CONST_SRC_CODE_COLOR_TINT_BASE = 0x2F,
		CONST_SRC_CODE_COLOR_TINT_DELTA = 0x30,
		CONST_SRC_CODE_COLOR_TINT_QUADRATIC_DELTA = 0x31,
		CONST_SRC_CODE_OUTDOOR_FEATHER_PARMS = 0x32,
		CONST_SRC_CODE_ENVMAP_PARMS = 0x33,
		CONST_SRC_CODE_SUN_SHADOWMAP_PIXEL_ADJUST = 0x34,
		CONST_SRC_CODE_SPOT_SHADOWMAP_PIXEL_ADJUST = 0x35,
		CONST_SRC_CODE_COMPOSITE_FX_DISTORTION = 0x36,
		CONST_SRC_CODE_POSTFX_FADE_EFFECT = 0x37,
		CONST_SRC_CODE_VIEWPORT_DIMENSIONS = 0x38,
		CONST_SRC_CODE_FRAMEBUFFER_READ = 0x39,
		CONST_SRC_CODE_FIXED_PS_END = 0x3A,
		CONST_SRC_CODE_NON_PS_BEGIN = 0x3A,
		CONST_SRC_CODE_BASE_LIGHTING_COORDS = 0x3A,
		CONST_SRC_CODE_LIGHT_PROBE_AMBIENT = 0x3B,
		CONST_SRC_CODE_NEARPLANE_ORG = 0x3C,
		CONST_SRC_CODE_NEARPLANE_DX = 0x3D,
		CONST_SRC_CODE_NEARPLANE_DY = 0x3E,
		CONST_SRC_CODE_CLIP_SPACE_LOOKUP_SCALE = 0x3F,
		CONST_SRC_CODE_CLIP_SPACE_LOOKUP_OFFSET = 0x40,
		CONST_SRC_CODE_PARTICLE_CLOUD_MATRIX0 = 0x41,
		CONST_SRC_CODE_PARTICLE_CLOUD_MATRIX1 = 0x42,
		CONST_SRC_CODE_PARTICLE_CLOUD_MATRIX2 = 0x43,
		CONST_SRC_CODE_PARTICLE_CLOUD_SPARK_COLOR0 = 0x44,
		CONST_SRC_CODE_PARTICLE_CLOUD_SPARK_COLOR1 = 0x45,
		CONST_SRC_CODE_PARTICLE_CLOUD_SPARK_COLOR2 = 0x46,
		CONST_SRC_CODE_PARTICLE_FOUNTAIN_PARM0 = 0x47,
		CONST_SRC_CODE_PARTICLE_FOUNTAIN_PARM1 = 0x48,
		CONST_SRC_CODE_DEPTH_FROM_CLIP = 0x49,
		CONST_SRC_CODE_CODE_MESH_ARG_0 = 0x4A,
		CONST_SRC_CODE_CODE_MESH_ARG_1 = 0x4B,
		CONST_SRC_CODE_CODE_MESH_ARG_LAST = 0x4B,
		CONST_SRC_CODE_NON_PS_END = 0x4C,
		CONST_SRC_CODE_COUNT_FLOAT4 = 0x4C,
		CONST_SRC_FIRST_CODE_MATRIX = 0x4C,
		CONST_SRC_CODE_VIEW_MATRIX = 0x4C,
		CONST_SRC_CODE_INVERSE_VIEW_MATRIX = 0x4D,
		CONST_SRC_CODE_TRANSPOSE_VIEW_MATRIX = 0x4E,
		CONST_SRC_CODE_INVERSE_TRANSPOSE_VIEW_MATRIX = 0x4F,
		CONST_SRC_CODE_PROJECTION_MATRIX = 0x50,
		CONST_SRC_CODE_INVERSE_PROJECTION_MATRIX = 0x51,
		CONST_SRC_CODE_TRANSPOSE_PROJECTION_MATRIX = 0x52,
		CONST_SRC_CODE_INVERSE_TRANSPOSE_PROJECTION_MATRIX = 0x53,
		CONST_SRC_CODE_VIEW_PROJECTION_MATRIX = 0x54,
		CONST_SRC_CODE_INVERSE_VIEW_PROJECTION_MATRIX = 0x55,
		CONST_SRC_CODE_TRANSPOSE_VIEW_PROJECTION_MATRIX = 0x56,
		CONST_SRC_CODE_INVERSE_TRANSPOSE_VIEW_PROJECTION_MATRIX = 0x57,
		CONST_SRC_CODE_SHADOW_LOOKUP_MATRIX = 0x58,
		CONST_SRC_CODE_INVERSE_SHADOW_LOOKUP_MATRIX = 0x59,
		CONST_SRC_CODE_TRANSPOSE_SHADOW_LOOKUP_MATRIX = 0x5A,
		CONST_SRC_CODE_INVERSE_TRANSPOSE_SHADOW_LOOKUP_MATRIX = 0x5B,
		CONST_SRC_CODE_WORLD_OUTDOOR_LOOKUP_MATRIX = 0x5C,
		CONST_SRC_CODE_INVERSE_WORLD_OUTDOOR_LOOKUP_MATRIX = 0x5D,
		CONST_SRC_CODE_TRANSPOSE_WORLD_OUTDOOR_LOOKUP_MATRIX = 0x5E,
		CONST_SRC_CODE_INVERSE_TRANSPOSE_WORLD_OUTDOOR_LOOKUP_MATRIX = 0x5F,
		CONST_SRC_CODE_WORLD_MATRIX0 = 0x60,
		CONST_SRC_CODE_INVERSE_WORLD_MATRIX0 = 0x61,
		CONST_SRC_CODE_TRANSPOSE_WORLD_MATRIX0 = 0x62,
		CONST_SRC_CODE_INVERSE_TRANSPOSE_WORLD_MATRIX0 = 0x63,
		CONST_SRC_CODE_WORLD_VIEW_MATRIX0 = 0x64,
		CONST_SRC_CODE_INVERSE_WORLD_VIEW_MATRIX0 = 0x65,
		CONST_SRC_CODE_TRANSPOSE_WORLD_VIEW_MATRIX0 = 0x66,
		CONST_SRC_CODE_INVERSE_TRANSPOSE_WORLD_VIEW_MATRIX0 = 0x67,
		CONST_SRC_CODE_WORLD_VIEW_PROJECTION_MATRIX0 = 0x68,
		CONST_SRC_CODE_INVERSE_WORLD_VIEW_PROJECTION_MATRIX0 = 0x69,
		CONST_SRC_CODE_TRANSPOSE_WORLD_VIEW_PROJECTION_MATRIX0 = 0x6A,
		CONST_SRC_CODE_INVERSE_TRANSPOSE_WORLD_VIEW_PROJECTION_MATRIX0 = 0x6B,
		CONST_SRC_CODE_WORLD_MATRIX1 = 0x6C,
		CONST_SRC_CODE_INVERSE_WORLD_MATRIX1 = 0x6D,
		CONST_SRC_CODE_TRANSPOSE_WORLD_MATRIX1 = 0x6E,
		CONST_SRC_CODE_INVERSE_TRANSPOSE_WORLD_MATRIX1 = 0x6F,
		CONST_SRC_CODE_WORLD_VIEW_MATRIX1 = 0x70,
		CONST_SRC_CODE_INVERSE_WORLD_VIEW_MATRIX1 = 0x71,
		CONST_SRC_CODE_TRANSPOSE_WORLD_VIEW_MATRIX1 = 0x72,
		CONST_SRC_CODE_INVERSE_TRANSPOSE_WORLD_VIEW_MATRIX1 = 0x73,
		CONST_SRC_CODE_WORLD_VIEW_PROJECTION_MATRIX1 = 0x74,
		CONST_SRC_CODE_INVERSE_WORLD_VIEW_PROJECTION_MATRIX1 = 0x75,
		CONST_SRC_CODE_TRANSPOSE_WORLD_VIEW_PROJECTION_MATRIX1 = 0x76,
		CONST_SRC_CODE_INVERSE_TRANSPOSE_WORLD_VIEW_PROJECTION_MATRIX1 = 0x77,
		CONST_SRC_CODE_WORLD_MATRIX2 = 0x78,
		CONST_SRC_CODE_INVERSE_WORLD_MATRIX2 = 0x79,
		CONST_SRC_CODE_TRANSPOSE_WORLD_MATRIX2 = 0x7A,
		CONST_SRC_CODE_INVERSE_TRANSPOSE_WORLD_MATRIX2 = 0x7B,
		CONST_SRC_CODE_WORLD_VIEW_MATRIX2 = 0x7C,
		CONST_SRC_CODE_INVERSE_WORLD_VIEW_MATRIX2 = 0x7D,
		CONST_SRC_CODE_TRANSPOSE_WORLD_VIEW_MATRIX2 = 0x7E,
		CONST_SRC_CODE_INVERSE_TRANSPOSE_WORLD_VIEW_MATRIX2 = 0x7F,
		CONST_SRC_CODE_WORLD_VIEW_PROJECTION_MATRIX2 = 0x80,
		CONST_SRC_CODE_INVERSE_WORLD_VIEW_PROJECTION_MATRIX2 = 0x81,
		CONST_SRC_CODE_TRANSPOSE_WORLD_VIEW_PROJECTION_MATRIX2 = 0x82,
		CONST_SRC_CODE_INVERSE_TRANSPOSE_WORLD_VIEW_PROJECTION_MATRIX2 = 0x83,
		CONST_SRC_TOTAL_COUNT = 0x84,
		CONST_SRC_NONE = 0x85,
	};

	enum FsThread
	{
		FS_THREAD_MAIN = 0x0,
		FS_THREAD_STREAM = 0x1,
		FS_THREAD_DATABASE = 0x2,
		FS_THREAD_BACKEND = 0x3,
		FS_THREAD_SERVER = 0x4,
		FS_THREAD_COUNT = 0x5,
		FS_THREAD_INVALID = 0x6,
	};

	enum TextureSemantic : char
	{
		TS_2D = 0x0,
		TS_FUNCTION = 0x1,
		TS_COLOR_MAP = 0x2,
		TS_DETAIL_MAP = 0x3,
		TS_UNUSED_2 = 0x4,
		TS_NORMAL_MAP = 0x5,
		TS_UNUSED_3 = 0x6,
		TS_UNUSED_4 = 0x7,
		TS_SPECULAR_MAP = 0x8,
		TS_UNUSED_5 = 0x9,
		TS_UNUSED_6 = 0xA,
		TS_WATER_MAP = 0xB,
	};


	enum materialSurfType_t
	{
		SURF_TYPE_DEFAULT,
		SURF_TYPE_BARK,
		SURF_TYPE_BRICK,
		SURF_TYPE_CARPET,
		SURF_TYPE_CLOTH,
		SURF_TYPE_CONCRETE,
		SURF_TYPE_DIRT,
		SURF_TYPE_FLESH,
		SURF_TYPE_FOLIAGE,
		SURF_TYPE_GLASS,
		SURF_TYPE_GRASS,
		SURF_TYPE_GRAVEL,
		SURF_TYPE_ICE,
		SURF_TYPE_METAL,
		SURF_TYPE_MUD,
		SURF_TYPE_PAPER,
		SURF_TYPE_PLASTER,
		SURF_TYPE_ROCK,
		SURF_TYPE_SAND,
		SURF_TYPE_SNOW,
		SURF_TYPE_WATER,
		SURF_TYPE_WOOD,
		SURF_TYPE_ASPHALT,
		SURF_TYPE_CERAMIC,
		SURF_TYPE_PLASTIC,
		SURF_TYPE_RUBBER,
		SURF_TYPE_CUSHION,
		SURF_TYPE_FRUIT,
		SURF_TYPE_PAINTED_METAL,
		SURF_TYPE_RIOT_SHIELD,
		SURF_TYPE_SLUSH,

		SURF_TYPE_COUNT
	};

	enum : unsigned __int16
	{
		DVAR_NONE = 0,	// No flags
		DVAR_ARCHIVE = 1 << 0,	// Set to cause it to be saved to config_mp.cfg of the client
		DVAR_LATCH = 1 << 1,	// Will only change when C code next does a Dvar_Get(), so it can't be changed
		// without proper initialization. Modified will be set, even though the value hasn't changed yet
		DVAR_CHEAT = 1 << 2,	// Can not be changed if cheats are disabled
		DVAR_CODINFO = 1 << 3,	// On change, this is sent to all clients (if you are host)
		DVAR_SCRIPTINFO = 1 << 4,
		DVAR_TEMP = 1 << 5, // Best educated guess
		DVAR_SAVED = 1 << 6,
		DVAR_INTERNAL = 1 << 7, // Best educated guess
		DVAR_EXTERNAL = 1 << 8,	// Created by a set command
		DVAR_USERINFO = 1 << 9,	// Sent to server on connect or change
		DVAR_SERVERINFO = 1 << 10, // Sent in response to front end requests
		DVAR_INIT = 1 << 11, // Don't allow change from console at all
		DVAR_SYSTEMINFO = 1 << 12, // Will be duplicated on all clients
		DVAR_ROM = 1 << 13, // Display only, cannot be set by user at all
		DVAR_CHANGEABLE_RESET = 1 << 14,
		DVAR_AUTOEXEC = 1 << 15, // isLoadingAutoExecGlobalFlag is always false so it should be never set by the game
	};

	enum ImageCategory : char
	{
		IMG_CATEGORY_UNKNOWN = 0x0,
		IMG_CATEGORY_AUTO_GENERATED = 0x1,
		IMG_CATEGORY_LIGHTMAP = 0x2,
		IMG_CATEGORY_LOAD_FROM_FILE = 0x3,
		IMG_CATEGORY_RAW = 0x4,
		IMG_CATEGORY_FIRST_UNMANAGED = 0x5,
		IMG_CATEGORY_WATER = 0x5,
		IMG_CATEGORY_RENDERTARGET = 0x6,
		IMG_CATEGORY_TEMP = 0x7,
	};

	enum buttons_t
	{
		KB_LEFT = 0x0,
		KB_RIGHT = 0x1,
		KB_FORWARD = 0x2,
		KB_BACK = 0x3,
		KB_LOOKUP = 0x4,
		KB_LOOKDOWN = 0x5,
		KB_MOVELEFT = 0x6,
		KB_MOVERIGHT = 0x7,
		KB_STRAFE = 0x8,
		KB_SPEED = 0x9,
		KB_UP = 0xA,
		KB_DOWN = 0xB,
		KB_ANYUP = 0xC,
		KB_MLOOK = 0xD,
		KB_ATTACK = 0xE,
		KB_BREATH = 0xF,
		KB_FRAG = 0x10,
		KB_OFFHANDSECONDARY = 0x11,
		KB_MELEE = 0x12,
		KB_ACTIVATE = 0x13,
		KB_RELOAD = 0x14,
		KB_USE_RELOAD = 0x15,
		KB_PRONE = 0x16,
		KB_CROUCH = 0x17,
		KB_THROW = 0x18,
		KB_SPRINT = 0x19,
		KB_NIGHTVISION = 0x1A,
		KB_TALK = 0x1B,
		NUM_BUTTONS = 0x1C
	};

	enum DvarSetSource
	{
		DVAR_SOURCE_INTERNAL = 0x0,
		DVAR_SOURCE_EXTERNAL = 0x1,
		DVAR_SOURCE_SCRIPT = 0x2,
		DVAR_SOURCE_DEVGUI = 0x3,
	};

	enum dvar_type : char
	{
		DVAR_TYPE_BOOL = 0x0,
		DVAR_TYPE_FLOAT = 0x1,
		DVAR_TYPE_FLOAT_2 = 0x2,
		DVAR_TYPE_FLOAT_3 = 0x3,
		DVAR_TYPE_FLOAT_4 = 0x4,
		DVAR_TYPE_INT = 0x5,
		DVAR_TYPE_ENUM = 0x6,
		DVAR_TYPE_STRING = 0x7,
		DVAR_TYPE_COLOR = 0x8,
		DVAR_TYPE_FLOAT_3_COLOR = 0x9,
		DVAR_TYPE_COUNT = 0xA,
	};

	enum clientState_t
	{
		CS_FREE = 0x0,
		CS_ZOMBIE = 0x1,
		CS_RECONNECTING = 0x2,
		CS_CONNECTED = 0x3,
		CS_CLIENTLOADING = 0x4,
		CS_ACTIVE = 0x5,
	};

	enum serverState_t
	{
		SS_DEAD = 0x0,
		SS_LOADING = 0x1,
		SS_GAME = 0x2,
	};

	enum GfxLightType
	{
		GFX_LIGHT_TYPE_NONE = 0x0,
		GFX_LIGHT_TYPE_DIR = 0x1,
		GFX_LIGHT_TYPE_SPOT = 0x2,
		GFX_LIGHT_TYPE_OMNI = 0x3,
		GFX_LIGHT_TYPE_COUNT = 0x4,
		GFX_LIGHT_TYPE_DIR_SHADOWMAP = 0x4,
		GFX_LIGHT_TYPE_SPOT_SHADOWMAP = 0x5,
		GFX_LIGHT_TYPE_OMNI_SHADOWMAP = 0x6,
		GFX_LIGHT_TYPE_COUNT_WITH_SHADOWMAP_VERSIONS = 0x7,
	};

	enum errorParm_t
	{
		ERR_FATAL = 0x0,
		ERR_DROP = 0x1,
		ERR_SERVERDISCONNECT = 0x2,
		ERR_DISCONNECT = 0x3,
		ERR_SCRIPT = 0x4,
		ERR_SCRIPT_DROP = 0x5,
		ERR_LOCALIZATION = 0x6,
		ERR_MAPLOADERRORSUMMARY = 0x7
	};

	enum ConfigString
	{
		CS_VOTE_TIME = 0x11,
		CS_VOTE_STRING = 0x12,
		CS_VOTE_YES = 0x13,
		CS_VOTE_NO = 0x14,
		CS_VOTE_MAPNAME = 0x15,
		CS_VOTE_GAMETYPE = 0x16,
		CS_MODELS = 0x465,	// Models (confirmed) 1125
		// 1580<>1637 models not cached (something's going on, not sure what)
		CS_MODELS_LAST = 0x664,	// End of models
		CS_SHELLSHOCKS = 0x985,
		CS_WEAPONFILES = 0xAF5, // 2805 Confirmed
		CS_WEAPONFILES_LAST = 0xFA3, // Confirmed too // 4003
		CS_ITEMS = 4138, // Correct! CS_ITEMS is actually an item **COUNT**

		CS_LAST = CS_ITEMS,
		MAX_CONFIGSTRINGS = 4139
	}; // Incomplete

	enum conChannel_t
	{
		CON_CHANNEL_DONT_FILTER,
		CON_CHANNEL_ERROR,
		CON_CHANNEL_GAMENOTIFY,
		CON_CHANNEL_BOLDGAME,
		CON_CHANNEL_SUBTITLE,
		CON_CHANNEL_OBITUARY,
		CON_CHANNEL_LOGFILEONLY,
		CON_CHANNEL_CONSOLEONLY,
		CON_CHANNEL_GFX,
		CON_CHANNEL_SOUND,
		CON_CHANNEL_FILES,
		CON_CHANNEL_DEVGUI,
		CON_CHANNEL_PROFILE,
		CON_CHANNEL_UI,
		CON_CHANNEL_CLIENT,
		CON_CHANNEL_SERVER,
		CON_CHANNEL_SYSTEM,
		CON_CHANNEL_PLAYERWEAP,
		CON_CHANNEL_AI,
		CON_CHANNEL_ANIM,
		CON_CHANNEL_PHYS,
		CON_CHANNEL_FX,
		CON_CHANNEL_LEADERBOARDS,
		CON_CHANNEL_PARSERSCRIPT,
		CON_CHANNEL_SCRIPT,
		CON_CHANNEL_NETWORK,

		CON_BUILTIN_CHANNEL_COUNT,
	};

	enum meansOfDeath_t
	{
		MOD_UNKNOWN = 0x0,
		MOD_PISTOL_BULLET = 0x1,
		MOD_RIFLE_BULLET = 0x2,
		MOD_EXPLOSIVE_BULLET = 0x3,
		MOD_GRENADE = 0x4,
		MOD_GRENADE_SPLASH = 0x5,
		MOD_PROJECTILE = 0x6,
		MOD_PROJECTILE_SPLASH = 0x7,
		MOD_MELEE = 0x8,
		MOD_HEAD_SHOT = 0x9,
		MOD_CRUSH = 0xA,
		MOD_FALLING = 0xB,
		MOD_SUICIDE = 0xC,
		MOD_TRIGGER_HURT = 0xD,
		MOD_EXPLOSIVE = 0xE,
		MOD_IMPACT = 0xF,
		MOD_NUM = 0x10,
	};

	enum
	{
		FL_GODMODE = 1 << 0,
		FL_DEMI_GODMODE = 1 << 1,
		FL_NOTARGET = 1 << 2,
		FL_NO_KNOCKBACK = 1 << 3,
		FL_NO_RADIUS_DAMAGE = 1 << 4,
		FL_SUPPORTS_LINKTO = 1 << 12,
		FL_NO_AUTO_ANIM_UPDATE = 1 << 13,
		FL_GRENADE_TOUCH_DAMAGE = 1 << 14,
		FL_STABLE_MISSILES = 1 << 17,
		FL_REPEAT_ANIM_UPDATE = 1 << 18,
		FL_VEHICLE_TARGET = 1 << 19,
		FL_GROUND_ENT = 1 << 20,
		FL_CURSOR_HINT = 1 << 21,
		FL_MISSILE_ATTRACTOR = 1 << 23,
		FL_WEAPON_BEING_GRABBED = 1 << 24,
		FL_DELETE = 1 << 25,
		FL_BOUNCE = 1 << 26,
		FL_MOVER_SLIDE = 1 << 27
	};

	enum ClassNum : unsigned int
	{
		CLASS_NUM_ENTITY = 0x0,
		CLASS_NUM_HUDELEM = 0x1,
		CLASS_NUM_PATHNODE = 0x2,
		CLASS_NUM_VEHICLENODE = 0x3,
		CLASS_NUM_VEHTRACK_SEGMENT = 0x4,
		CLASS_NUM_FXENTITY = 0x5,
		CLASS_NUM_COUNT = 0x6,
	};

	enum hitLocation_t
	{
		HITLOC_NONE,
		HITLOC_HELMET,
		HITLOC_HEAD,
		HITLOC_NECK,
		HITLOC_TORSO_UPR,
		HITLOC_TORSO_LWR,
		HITLOC_R_ARM_UPR,
		HITLOC_L_ARM_UPR,
		HITLOC_R_ARM_LWR,
		HITLOC_L_ARM_LWR,
		HITLOC_R_HAND,
		HITLOC_L_HAND,
		HITLOC_R_LEG_UPR,
		HITLOC_L_LEG_UPR,
		HITLOC_R_LEG_LWR,
		HITLOC_L_LEG_LWR,
		HITLOC_R_FOOT,
		HITLOC_L_FOOT,
		HITLOC_GUN,
		HITLOC_SHIELD,
		HITLOC_NUM
	};

	enum svscmd_type
	{
		SV_CMD_CAN_IGNORE = 0x0,
		SV_CMD_RELIABLE = 0x1,
	};

	enum RumbleSourceType
	{
		RUMBLESOURCE_INVALID = 0x0,
		RUMBLESOURCE_ENTITY = 0x1,
		RUMBLESOURCE_POS = 0x2,
	};

	struct FxEffectDef;
	struct pathnode_t;
	struct pathnode_tree_t;
	struct GfxPortal;
	struct Statement_s;
	struct MenuEventHandlerSet;
	struct menuDef_t;

	struct cspField_t
	{
		const char* szName;
		int iOffset;
		int iFieldType;
	};

	struct CmdArgs
	{
		int nesting;
		int localClientNum[8];
		int controllerIndex[8];
		int argc[8];
		const char** argv[8];
	};

	static_assert(sizeof(CmdArgs) == 0x84);

	struct cmd_function_s
	{
		cmd_function_s* next;
		const char* name;
		const char* autoCompleteDir;
		const char* autoCompleteExt;
		void(__cdecl* function)();
		int flags;
	};

#pragma pack(push, 4)
	struct kbutton_t
	{
		int down[2];
		unsigned int downtime;
		unsigned int msec;
		bool active;
		bool wasPressed;
	};
#pragma pack(pop)

	enum PlayerHandIndex
	{
		WEAPON_HAND_RIGHT = 0x0,
		WEAPON_HAND_LEFT = 0x1,
		NUM_WEAPON_HANDS = 0x2,
		WEAPON_HAND_DEFAULT = 0x0,
	};

	enum KeyCatch_t
	{
		KEYCATCH_MASK_ANY = -1,
		KEYCATCH_CONSOLE = 0x1,
		KEYCATCH_UNKNOWN2 = 0x2,
		KEYCATCH_UNKNOWN4 = 0x4,
		KEYCATCH_LOCATION_SELECTION = 0x8,
		KEYCATCH_UI = 0x10,
		KEYCATCH_CHAT = 0x20,
		KEYCATCH_UNKNOWN40 = 0x40,
		KEYCATCH_UNKNOWN80 = 0x80,
		KEYCATCH_UNKNOWN100 = 0x100,
	};

	enum keyNum_t
	{
		K_NONE = 0x0,
		K_FIRSTGAMEPADBUTTON_RANGE_1 = 0x1, // First Gamepad 1
		K_BUTTON_A = 0x1,
		K_BUTTON_B = 0x2,
		K_BUTTON_X = 0x3,
		K_BUTTON_Y = 0x4,
		K_BUTTON_LSHLDR = 0x5,
		K_BUTTON_RSHLDR = 0x6,
		K_LASTGAMEPADBUTTON_RANGE_1 = 0x6, // Last Gamepad 1
		K_TAB = 0x9,
		K_ENTER = 0xD,
		K_FIRSTGAMEPADBUTTON_RANGE_2 = 0xE, // First Gamepad 2
		K_BUTTON_START = 0xE,
		K_BUTTON_BACK = 0xF,
		K_BUTTON_LSTICK = 0x10,
		K_BUTTON_RSTICK = 0x11,
		K_BUTTON_LTRIG = 0x12,
		K_BUTTON_RTRIG = 0x13,
		K_FIRSTDPAD = 0x14, // First Dpad
		K_DPAD_UP = 0x14,
		K_DPAD_DOWN = 0x15,
		K_DPAD_LEFT = 0x16,
		K_DPAD_RIGHT = 0x17,
		K_LASTDPAD = 0x17, // Last Dpad
		K_DPAD_LEFTRIGHT = 0x18,
		K_DPAD_UPDOWN = 0x19,
		K_LASTGAMEPADBUTTON_RANGE_2 = 0x19, // Last Gamepad 2
		K_ESCAPE = 0x1B,
		K_FIRSTGAMEPADBUTTON_RANGE_3 = 0x1C, // First Gamepad 3
		K_FIRSTAPAD = 0x1C, // First APad
		K_APAD_UP = 0x1C,
		K_APAD_DOWN = 0x1D,
		K_APAD_LEFT = 0x1E,
		K_APAD_RIGHT = 0x1F,
		K_LASTAPAD = 0x1F, // Last APad
		K_LASTGAMEPADBUTTON_RANGE_3 = 0x1F, // Last Gamepad 3
		K_SPACE = 0x20,
		K_BACKSPACE = 0x7F,
		K_ASCII_FIRST = 0x80,
		K_ASCII_181 = 0x80,
		K_ASCII_191 = 0x81,
		K_ASCII_223 = 0x82,
		K_ASCII_224 = 0x83,
		K_ASCII_225 = 0x84,
		K_ASCII_228 = 0x85,
		K_ASCII_229 = 0x86,
		K_ASCII_230 = 0x87,
		K_ASCII_231 = 0x88,
		K_ASCII_232 = 0x89,
		K_ASCII_233 = 0x8A,
		K_ASCII_236 = 0x8B,
		K_ASCII_241 = 0x8C,
		K_ASCII_242 = 0x8D,
		K_ASCII_243 = 0x8E,
		K_ASCII_246 = 0x8F,
		K_ASCII_248 = 0x90,
		K_ASCII_249 = 0x91,
		K_ASCII_250 = 0x92,
		K_ASCII_252 = 0x93,
		K_END_ASCII_CHARS = 0x94,
		K_COMMAND = 0x96,
		K_CAPSLOCK = 0x97,
		K_POWER = 0x98,
		K_PAUSE = 0x99,
		K_UPARROW = 0x9A,
		K_DOWNARROW = 0x9B,
		K_LEFTARROW = 0x9C,
		K_RIGHTARROW = 0x9D,
		K_ALT = 0x9E,
		K_CTRL = 0x9F,
		K_SHIFT = 0xA0,
		K_INS = 0xA1,
		K_DEL = 0xA2,
		K_PGDN = 0xA3,
		K_PGUP = 0xA4,
		K_HOME = 0xA5,
		K_END = 0xA6,
		K_F1 = 0xA7,
		K_F2 = 0xA8,
		K_F3 = 0xA9,
		K_F4 = 0xAA,
		K_F5 = 0xAB,
		K_F6 = 0xAC,
		K_F7 = 0xAD,
		K_F8 = 0xAE,
		K_F9 = 0xAF,
		K_F10 = 0xB0,
		K_F11 = 0xB1,
		K_F12 = 0xB2,
		K_F13 = 0xB3,
		K_F14 = 0xB4,
		K_F15 = 0xB5,
		K_KP_HOME = 0xB6,
		K_KP_UPARROW = 0xB7,
		K_KP_PGUP = 0xB8,
		K_KP_LEFTARROW = 0xB9,
		K_KP_5 = 0xBA,
		K_KP_RIGHTARROW = 0xBB,
		K_KP_END = 0xBC,
		K_KP_DOWNARROW = 0xBD,
		K_KP_PGDN = 0xBE,
		K_KP_ENTER = 0xBF,
		K_KP_INS = 0xC0,
		K_KP_DEL = 0xC1,
		K_KP_SLASH = 0xC2,
		K_KP_MINUS = 0xC3,
		K_KP_PLUS = 0xC4,
		K_KP_NUMLOCK = 0xC5,
		K_KP_STAR = 0xC6,
		K_KP_EQUALS = 0xC7,
		K_MOUSE1 = 0xC8,
		K_MOUSE2 = 0xC9,
		K_MOUSE3 = 0xCA,
		K_MOUSE4 = 0xCB,
		K_MOUSE5 = 0xCC,
		K_MWHEELDOWN = 0xCD,
		K_MWHEELUP = 0xCE,
		K_AUX1 = 0xCF,
		K_AUX2 = 0xD0,
		K_AUX3 = 0xD1,
		K_AUX4 = 0xD2,
		K_AUX5 = 0xD3,
		K_AUX6 = 0xD4,
		K_AUX7 = 0xD5,
		K_AUX8 = 0xD6,
		K_AUX9 = 0xD7,
		K_AUX10 = 0xD8,
		K_AUX11 = 0xD9,
		K_AUX12 = 0xDA,
		K_AUX13 = 0xDB,
		K_AUX14 = 0xDC,
		K_AUX15 = 0xDD,
		K_AUX16 = 0xDE,
		K_LAST_KEY = 0xDF,
	};

	enum uiMenuCommand_t
	{
		UIMENU_NONE = 0x0,
		UIMENU_MAIN = 0x1,
		UIMENU_INGAME = 0x2,
		UIMENU_PREGAME = 0x3,
		UIMENU_POSTGAME = 0x4,
		UIMENU_SCRIPT_POPUP = 0x5,
		UIMENU_SCOREBOARD = 0x6,
		UIMENU_PARTY = 0x7,
		UIMENU_GAMELOBBY = 0x8,
		UIMENU_PRIVATELOBBY = 0x9,
		UIMENU_ENDOFGAME = 0xA,
		UIMENU_MIGRATION = 0xB,
	};

	struct __declspec(align(4)) PhysPreset
	{
		const char* name;
		int type;
		float mass;
		float bounce;
		float friction;
		float bulletForceScale;
		float explosiveForceScale;
		const char* sndAliasPrefix;
		float piecesSpreadFraction;
		float piecesUpwardVelocity;
		bool tempDefaultToCylinder;
		bool perSurfaceSndAlias;
	};

	struct Bounds
	{
		float midPoint[3];
		float halfSize[3];
	};

	struct cplane_s
	{
		float normal[3];
		float dist;
		unsigned char type;
		unsigned char pad[3];
	};

	struct cbrushside_t
	{
		cplane_s* plane;
		unsigned __int16 materialNum;
		char firstAdjacentSideOffset;
		char edgeCount;
	};

	struct cbrush_t
	{
		unsigned short numsides;
		unsigned short glassPieceIndex;
		cbrushside_t* sides;
		unsigned char* baseAdjacentSide;
		unsigned short axialMaterialNum[2][3];
		unsigned char firstAdjacentSideOffsets[2][3];
		unsigned char edgeCount[2][3];
	};

	struct BrushWrapper
	{
		Bounds bounds;
		cbrush_t brush;
		int totalEdgeCount;
		cplane_s* planes;
	};

	struct PhysGeomInfo
	{
		BrushWrapper* brushWrapper;
		int type;
		float orientation[3][3];
		Bounds bounds;
	};

	struct PhysMass
	{
		float centerOfMass[3];
		float momentsOfInertia[3];
		float productsOfInertia[3];
	};

	struct PhysCollmap
	{
		const char* name;
		unsigned int count;
		PhysGeomInfo* geoms;
		PhysMass mass;
		Bounds bounds;
	};

	union XAnimIndices
	{
		char* _1;
		unsigned __int16* _2;
		void* data;
	};

	struct XAnimNotifyInfo
	{
		unsigned __int16 name;
		float time;
	};

	union XAnimDynamicFrames
	{
		uint8_t(*_1)[3];
		unsigned __int16(*_2)[3];
	};

	union XAnimDynamicIndices
	{
		char _1[1];
		unsigned __int16 _2[1];
	};

	struct __declspec(align(4)) XAnimPartTransFrames
	{
		float mins[3];
		float size[3];
		XAnimDynamicFrames frames;
		XAnimDynamicIndices indices;
	};

	union XAnimPartTransData
	{
		XAnimPartTransFrames frames;
		float frame0[3];
	};

	struct XAnimPartTrans
	{
		unsigned __int16 size;
		char smallTrans;
		XAnimPartTransData u;
	};

	struct __declspec(align(4)) XAnimDeltaPartQuatDataFrames2
	{
		__int16(*frames)[2];
		XAnimDynamicIndices indices;
	};

	union XAnimDeltaPartQuatData2
	{
		XAnimDeltaPartQuatDataFrames2 frames;
		__int16 frame0[2];
	};

	struct XAnimDeltaPartQuat2
	{
		unsigned __int16 size;
		XAnimDeltaPartQuatData2 u;
	};

	struct __declspec(align(4)) XAnimDeltaPartQuatDataFrames
	{
		__int16(*frames)[4];
		XAnimDynamicIndices indices;
	};

	union XAnimDeltaPartQuatData
	{
		XAnimDeltaPartQuatDataFrames frames;
		__int16 frame0[4];
	};

	struct XAnimDeltaPartQuat
	{
		unsigned __int16 size;
		XAnimDeltaPartQuatData u;
	};

	struct XAnimDeltaPart
	{
		XAnimPartTrans* trans;
		XAnimDeltaPartQuat2* quat2;
		XAnimDeltaPartQuat* quat;
	};

	struct XAnimParts
	{
		const char* name;
		unsigned __int16 dataByteCount;
		unsigned __int16 dataShortCount;
		unsigned __int16 dataIntCount;
		unsigned __int16 randomDataByteCount;
		unsigned __int16 randomDataIntCount;
		unsigned __int16 numframes;
		char flags;
		unsigned char boneCount[10];
		unsigned char notifyCount;
		char assetType;
		bool isDefault;
		unsigned int randomDataShortCount;
		unsigned int indexCount;
		float framerate;
		float frequency;
		unsigned __int16* names;
		char* dataByte;
		__int16* dataShort;
		int* dataInt;
		__int16* randomDataShort;
		char* randomDataByte;
		int* randomDataInt;
		XAnimIndices indices;
		XAnimNotifyInfo* notify;
		XAnimDeltaPart* deltaPart;
	};

	struct XSurfaceVertexInfo
	{
		unsigned __int16 vertCount[4];
		unsigned __int16* vertsBlend;
	};

	union GfxColor
	{
		unsigned int packed;
		unsigned char array[4];
	};

	union PackedTexCoords
	{
		unsigned int packed;
	};

	union PackedUnitVec
	{
		unsigned int packed;
		char array[4];
	};

	struct GfxPackedVertex
	{
		float xyz[3];
		float binormalSign;
		GfxColor color;
		PackedTexCoords texCoord;
		PackedUnitVec normal;
		PackedUnitVec tangent;
	};

	struct XSurfaceCollisionAabb
	{
		unsigned __int16 mins[3];
		unsigned __int16 maxs[3];
	};

	struct XSurfaceCollisionNode
	{
		XSurfaceCollisionAabb aabb;
		unsigned __int16 childBeginIndex;
		unsigned __int16 childCount;
	};

	struct XSurfaceCollisionLeaf
	{
		unsigned __int16 triangleBeginIndex;
	};

	struct XSurfaceCollisionTree
	{
		float trans[3];
		float scale[3];
		unsigned int nodeCount;
		XSurfaceCollisionNode* nodes;
		unsigned int leafCount;
		XSurfaceCollisionLeaf* leafs;
	};

	struct XRigidVertList
	{
		unsigned __int16 boneOffset;
		unsigned __int16 vertCount;
		unsigned __int16 triOffset;
		unsigned __int16 triCount;
		XSurfaceCollisionTree* collisionTree;
	};

	struct DObjSkelMat
	{
		float axis[3][4];
		float origin[4];
	};

	struct XSurface
	{
		char tileMode;
		bool deformed;
		unsigned __int16 vertCount;
		unsigned __int16 triCount;
		char zoneHandle;
		unsigned __int16 baseTriIndex;
		unsigned __int16 baseVertIndex;
		unsigned __int16* triIndices;
		XSurfaceVertexInfo vertInfo;
		GfxPackedVertex* verts0;
		unsigned int vertListCount;
		XRigidVertList* vertList;
		int partBits[6];
	};

	struct XModelSurfs
	{
		const char* name;
		XSurface* surfs;
		unsigned __int16 numsurfs;
		int partBits[6];
	};

	struct DObjAnimMat
	{
		float quat[4];
		float trans[3];
		float transWeight;
	};

	struct GfxDrawSurfFields
	{
		unsigned __int64 objectId : 16;
		unsigned __int64 reflectionProbeIndex : 8;
		unsigned __int64 hasGfxEntIndex : 1;
		unsigned __int64 customIndex : 5;
		unsigned __int64 materialSortedIndex : 12;
		unsigned __int64 prepass : 2;
		unsigned __int64 useHeroLighting : 1;
		unsigned __int64 sceneLightIndex : 8;
		unsigned __int64 surfType : 4;
		unsigned __int64 primarySortKey : 6;
		unsigned __int64 unused : 1;
	};

	union GfxDrawSurf
	{
		GfxDrawSurfFields fields;
		unsigned __int64 packed;
	};

	struct MaterialInfo
	{
		const char* name;
		unsigned char gameFlags;
		unsigned char sortKey;
		unsigned char textureAtlasRowCount;
		unsigned char textureAtlasColumnCount;
		GfxDrawSurf drawSurf;
		unsigned int surfaceTypeBits;
		unsigned __int16 hashIndex;
	};

	struct MaterialStreamRouting
	{
		char source;
		char dest;
	};

	struct MaterialVertexStreamRouting
	{
		MaterialStreamRouting data[13];
		IDirect3DVertexDeclaration9* decl[16];
	};

	struct MaterialVertexDeclaration
	{
		const char* name;
		char streamCount;
		bool hasOptionalSource;
		MaterialVertexStreamRouting routing;
	};

	struct GfxVertexShaderLoadDef
	{
		unsigned int* program;
		unsigned __int16 programSize;
		unsigned __int16 loadForRenderer;
	};

	struct MaterialVertexShaderProgram
	{
		IDirect3DVertexShader9* vs;
		GfxVertexShaderLoadDef loadDef;
	};

	struct MaterialVertexShader
	{
		const char* name;
		MaterialVertexShaderProgram prog;
	};

	struct GfxPixelShaderLoadDef
	{
		unsigned int* program;
		unsigned __int16 programSize;
		unsigned __int16 loadForRenderer;
	};

	struct MaterialPixelShaderProgram
	{
		IDirect3DPixelShader9* ps;
		GfxPixelShaderLoadDef loadDef;
	};

	struct MaterialPixelShader
	{
		const char* name;
		MaterialPixelShaderProgram prog;
	};


	enum MaterialShaderArgumentType : unsigned __int16
	{
		MTL_ARG_MATERIAL_VERTEX_CONST = 0x0,
		MTL_ARG_LITERAL_VERTEX_CONST = 0x1,
		MTL_ARG_MATERIAL_PIXEL_SAMPLER = 0x2,
		MTL_ARG_CODE_PRIM_BEGIN = 0x3,
		MTL_ARG_CODE_VERTEX_CONST = 0x3,
		MTL_ARG_CODE_PIXEL_SAMPLER = 0x4,
		MTL_ARG_CODE_PIXEL_CONST = 0x5,
		MTL_ARG_CODE_PRIM_END = 0x6,
		MTL_ARG_MATERIAL_PIXEL_CONST = 0x6,
		MTL_ARG_LITERAL_PIXEL_CONST = 0x7,
		MTL_ARG_COUNT = 0x8,
	};


	struct MaterialArgumentCodeConst
	{
		unsigned __int16 index;
		char firstRow;
		char rowCount;
	};

	union MaterialArgumentDef
	{
		float* literalConst;
		MaterialArgumentCodeConst codeConst;
		unsigned int codeSampler;
		unsigned int nameHash;
	};

	struct MaterialShaderArgument
	{
		MaterialShaderArgumentType type;
		unsigned __int16 dest;
		MaterialArgumentDef u;
	};

	struct MaterialPass
	{
		MaterialVertexDeclaration* vertexDecl;
		MaterialVertexShader* vertexShader;
		MaterialPixelShader* pixelShader;
		char perPrimArgCount;
		char perObjArgCount;
		char stableArgCount;
		char customSamplerFlags;
		MaterialShaderArgument* args;
	};

	struct visionSetVars_t
	{
		bool glowEnable;
		float glowBloomCutoff;
		float glowBloomDesaturation;
		float glowBloomIntensity0;
		float glowBloomIntensity1;
		float glowRadius0;
		float glowRadius1;
		float glowSkyBleedIntensity0;
		float glowSkyBleedIntensity1;
		bool filmEnable;
		float filmBrightness;
		float filmContrast;
		float filmDesaturation;
		float filmDesaturationDark;
		bool filmInvert;
		float filmLightTint[3];
		float filmMediumTint[3];
		float filmDarkTint[3];
		bool charPrimaryUseTweaks;
		float charPrimaryDiffuseScale;
		float charPrimarySpecularScale;
	};

	struct visField_t
	{
		const char* name;
		int offset;
		// 0 is for int, 1 is for float, otherwise it's a vector
		int fieldType;
	};

	enum OffhandClass
	{
		OFFHAND_CLASS_NONE = 0x0,
		OFFHAND_CLASS_FRAG_GRENADE = 0x1,
		OFFHAND_CLASS_SMOKE_GRENADE = 0x2,
		OFFHAND_CLASS_FLASH_GRENADE = 0x3,
		OFFHAND_CLASS_THROWINGKNIFE = 0x4,
		OFFHAND_CLASS_OTHER = 0x5,
		OFFHAND_CLASS_COUNT = 0x6,
	};

	enum ViewLockTypes
	{
		PLAYERVIEWLOCK_NONE = 0x0,
		PLAYERVIEWLOCK_FULL = 0x1,
		PLAYERVIEWLOCK_WEAPONJITTER = 0x2,
		PLAYERVIEWLOCKCOUNT = 0x3,
	};

	struct SprintState
	{
		int sprintButtonUpRequired;
		int sprintDelay;
		int lastSprintStart;
		int lastSprintEnd;
		int sprintStartMaxLength;
	};

	struct MantleState
	{
		float yaw;
		int timer;
		int transIndex;
		int flags;
	};

	struct PlayerActiveWeaponState
	{
		int weapAnim;
		int weaponTime;
		int weaponDelay;
		int weaponRestrictKickTime;
		int weaponState;
		int weapHandFlags;
		unsigned int weaponShotCount;
	};

	struct PlayerEquippedWeaponState
	{
		bool usedBefore;
		bool dualWielding;
		char weaponModel;
		bool needsRechamber[2];
	};

	struct GlobalAmmo
	{
		int ammoType;
		int ammoCount;
	};

	struct ClipAmmo
	{
		int clipIndex;
		int ammoCount[2];
	};

	struct PlayerWeaponCommonState
	{
		int offHandIndex;
		OffhandClass offhandPrimary;
		OffhandClass offhandSecondary;
		unsigned int weapon;
		unsigned int primaryWeaponForAltMode;
		int weapFlags;
		float fWeaponPosFrac;
		float aimSpreadScale;
		int adsDelayTime;
		int spreadOverride;
		int spreadOverrideState;
		PlayerHandIndex lastWeaponHand;
		GlobalAmmo ammoNotInClip[15];
		ClipAmmo ammoInClip[15];
		int weapLockFlags;
		int weapLockedEntnum;
		float weapLockedPos[3];
		int weaponIdleTime;
	};

	enum ActionSlotType
	{
		ACTIONSLOTTYPE_DONOTHING = 0x0,
		ACTIONSLOTTYPE_SPECIFYWEAPON = 0x1,
		ACTIONSLOTTYPE_ALTWEAPONTOGGLE = 0x2,
		ACTIONSLOTTYPE_NIGHTVISION = 0x3,
		ACTIONSLOTTYPECOUNT = 0x4,
	};

	struct ActionSlotParam_SpecifyWeapon
	{
		unsigned int index;
	};

	struct ActionSlotParam
	{
		ActionSlotParam_SpecifyWeapon specifyWeapon;
	};

	enum objectiveState_t
	{
		OBJST_EMPTY = 0x0,
		OBJST_ACTIVE = 0x1,
		OBJST_INVISIBLE = 0x2,
		OBJST_DONE = 0x3,
		OBJST_CURRENT = 0x4,
		OBJST_FAILED = 0x5,
		OBJST_NUMSTATES = 0x6,
	};

	struct objective_t
	{
		objectiveState_t state;
		float origin[3];
		int entNum;
		int teamNum;
		int icon;
	};

	enum he_type_t
	{
		HE_TYPE_FREE = 0x0,
		HE_TYPE_TEXT = 0x1,
		HE_TYPE_VALUE = 0x2,
		HE_TYPE_PLAYERNAME = 0x3,
		HE_TYPE_MAPNAME = 0x4,
		HE_TYPE_GAMETYPE = 0x5,
		HE_TYPE_MATERIAL = 0x6,
		HE_TYPE_TIMER_DOWN = 0x7,
		HE_TYPE_TIMER_UP = 0x8,
		HE_TYPE_TIMER_STATIC = 0x9,
		HE_TYPE_TENTHS_TIMER_DOWN = 0xA,
		HE_TYPE_TENTHS_TIMER_UP = 0xB,
		HE_TYPE_TENTHS_TIMER_STATIC = 0xC,
		HE_TYPE_CLOCK_DOWN = 0xD,
		HE_TYPE_CLOCK_UP = 0xE,
		HE_TYPE_WAYPOINT = 0xF,
		HE_TYPE_COUNT = 0x10,
	};

	struct hud_color
	{
		char r;
		char g;
		char b;
		char a;
	};

	union hudelem_color_t
	{
		hud_color __s0;
		int rgba;
	};

	struct hudelem_s
	{
		he_type_t type;
		float x;
		float y;
		float z;
		int targetEntNum;
		float fontScale;
		float fromFontScale;
		int fontScaleStartTime;
		int fontScaleTime;
		int font;
		int alignOrg;
		int alignScreen;
		hudelem_color_t color;
		hudelem_color_t fromColor;
		int fadeStartTime;
		int fadeTime;
		int label;
		int width;
		int height;
		int materialIndex;
		int fromWidth;
		int fromHeight;
		int scaleStartTime;
		int scaleTime;
		float fromX;
		float fromY;
		int fromAlignOrg;
		int fromAlignScreen;
		int moveStartTime;
		int moveTime;
		int time;
		int duration;
		float value;
		int text;
		float sort;
		hudelem_color_t glowColor;
		int fxBirthTime;
		int fxLetterTime;
		int fxDecayStartTime;
		int fxDecayDuration;
		int soundID;
		int flags;
	};

	struct game_hudelem_s
	{
		hudelem_s elem;
		int clientNum;
		int team;
		int archived;
	};

	enum
	{
		PMF_PRONE = 1 << 0,
		PMF_DUCKED = 1 << 1,
		PMF_MANTLE = 1 << 2,
		PMF_LADDER = 1 << 3,
		PMF_SIGHT_AIMING = 1 << 4,
		PMF_BACKWARDS_RUN = 1 << 5,
		PMF_WALKING = 1 << 6,
		PMF_TIME_HARDLANDING = 1 << 7,
		PMF_TIME_KNOCKBACK = 1 << 8,
		PMF_PRONEMOVE_OVERRIDDEN = 1 << 9,
		PMF_RESPAWNED = 1 << 10,
		PMF_FROZEN = 1 << 11,
		PMF_LADDER_FALL = 1 << 12,
		PMF_JUMPING = 1 << 13,
		PMF_SPRINTING = 1 << 14,
		PMF_SHELLSHOCKED = 1 << 15,
		PMF_MELEE_CHARGE = 1 << 16,
		PMF_NO_SPRINT = 1 << 17,
		PMF_NO_JUMP = 1 << 18,
		PMF_REMOTE_CONTROLLING = 1 << 19,
		PMF_ANIM_SCRIPTED = 1 << 20,
		PMF_UNK1 = 1 << 21,
		PMF_DIVING = 1 << 22,
	};

	enum
	{
		POF_INVULNERABLE = 1 << 0,
		POF_REMOTE_EYES = 1 << 1,
		POF_LASER_ALTVIEW = 1 << 2,
		POF_THERMAL_VISION = 1 << 3,
		POF_THERMAL_VISION_OVERLAY_FOF = 1 << 4,
		POF_REMOTE_CAMERA_SOUNDS = 1 << 5,
		POF_ALT_SCENE_REAR_VIEW = 1 << 6,
		POF_ALT_SCENE_TAG_VIEW = 1 << 7,
		POF_SHIELD_ATTACHED_TO_WORLD_MODEL = 1 << 8,
		POF_DONT_LERP_VIEWANGLES = 1 << 9,
		POF_EMP_JAMMED = 1 << 10,
		POF_FOLLOW = 1 << 11,
		POF_PLAYER = 1 << 12,
		POF_SPEC_ALLOW_CYCLE = 1 << 13,
		POF_SPEC_ALLOW_FREELOOK = 1 << 14,
		POF_AC130 = 1 << 15,
		POF_COMPASS_PING = 1 << 16,
		POF_ADS_THIRD_PERSON_TOGGLE = 1 << 17,
	};

	enum pmtype_t
	{
		PM_NORMAL = 0x0,
		PM_NORMAL_LINKED = 0x1,
		PM_NOCLIP = 0x2,
		PM_UFO = 0x3,
		PM_MPVIEWER = 0x4,
		PM_SPECTATOR = 0x5,
		PM_INTERMISSION = 0x6,
		PM_LASTSTAND = 0x7,
		PM_DEAD = 0x8,
		PM_DEAD_LINKED = 0x9,
	};

	enum
	{
		EF_NONSOLID_BMODEL = 1 << 0,
		EF_TELEPORT_BIT = 1 << 1,
		EF_CROUCHING = 1 << 2,
		EF_PRONE = 1 << 3,
		EF_UNK1 = 1 << 4,
		EF_NODRAW = 1 << 5,
		EF_TIMED_OBJECT = 1 << 6,
		EF_VOTED = 1 << 7,
		EF_TALK = 1 << 8,
		EF_FIRING = 1 << 9,
		EF_TURRET_ACTIVE_PRONE = 1 << 10,
		EF_TURRET_ACTIVE_DUCK = 1 << 11,
		EF_LOCK_LIGHT_VIS = 1 << 12,
		EF_AIM_ASSIST = 1 << 13,
		EF_LOOP_RUMBLE = 1 << 14,
		EF_LASER_SIGHT = 1 << 15,
		EF_MANTLE = 1 << 16,
		EF_DEAD = 1 << 17,
		EF_ADS = 1 << 18,
		EF_NEW = 1 << 19,
		EF_VEHICLE_ACTIVE = 1 << 20,
		EF_JAMMING = 1 << 21,
		EF_COMPASS_PING = 1 << 22,
		EF_SOFT = 1 << 23,
	};

	enum
	{
		PLF_ANGLES_LOCKED = 1 << 0,
		PLF_USES_OFFSET = 1 << 1,
		PLF_WEAPONVIEW_ONLY = 1 << 2,
	};

	enum
	{
		PWF_USE_RELOAD = 1 << 0,
		PWF_USING_OFFHAND = 1 << 1,
		PWF_HOLDING_BREATH = 1 << 2,
		PWF_FRIENDLY_FIRE = 1 << 3,
		PWF_ENEMY_FIRE = 1 << 4,
		PWF_NO_ADS = 1 << 5,
		PWF_USING_NIGHTVISION = 1 << 6,
		PWF_DISABLE_WEAPONS = 1 << 7,
		PWF_TRIGGER_LEFT_FIRE = 1 << 8,
		PWF_TRIGGER_DOUBLE_FIRE = 1 << 9,
		PWF_USING_RECOILSCALE = 1 << 10,
		PWF_DISABLE_WEAPON_SWAPPING = 1 << 11,
		PWF_DISABLE_OFFHAND_WEAPONS = 1 << 12,
		PWF_SWITCHING_TO_RIOTSHIELD = 1 << 13,
		// IW5 flags backported
		PWF_DISABLE_WEAPON_PICKUP = 1 << 16
	};

	enum perksEnum
	{
		PERK_JAMRADAR = 0x0,
		PERK_ACCURACY = 0x1,
		PERK_FASTRELOAD = 0x2,
		PERK_RATEOFFIRE = 0x3,
		PERK_EXTRABREATH = 0x4,
		PERK_EXTRABP = 0x5,
		PERK_GRENADEDEATH = 0x6,
		PERK_PISTOLDEATH = 0x7,
		PERK_QUIETMOVE = 0x8,
		PERK_PARABOLIC = 0x9,
		PERK_LONGERSPRINT = 0xA,
		PERK_DETECTEXPLOSIVE = 0xB,
		PERK_EXPOSEENEMY = 0xC,
		PERK_BULLETDMG = 0xD,
		PERK_EXTRAAMMO = 0xE,
		PERK_TWOPRIMARIES = 0xF,
		PERK_ARMORVEST = 0x10,
		PERK_FRAGGRENADE = 0x11,
		PERK_SPECIALGRENADE = 0x12,
		PERK_FASTMANTLE = 0x13,
		PERK_JUMPDIVE = 0x14,
		PERK_EXPLOSIVEBULLETS = 0x15,
		PERK_SCAVENGER = 0x16,
		PERK_EXTENDEDMAGS = 0x17,
		PERK_LIGHTWEIGHT = 0x18,
		PERK_MARATHON = 0x19,
		PERK_QUICKDRAW = 0x1A,
		PERK_COLDBLOODED = 0x1B,
		PERK_HEARTBREAKER = 0x1C,
		PERK_SELECTIVEHEARING = 0x1D,
		PERK_FASTSNIPE = 0x1E,
		PERK_IMPROVEDEXTRABREATH = 0x1F,
		PERK_SPYGAME = 0x20,
		PERK_AUTOMANTLE = 0x21,
		PERK_FASTSPRINTRECOVERY = 0x22,
		PERK_EXTENDEDMELEE = 0x23,
		PERK_COUNT = 0x24,
		PERK_UNKNOWN = 0x24,
	};

	constexpr std::size_t PERK_ARRAY_COUNT = 2;

	struct playerState_s
	{
		int commandTime;
		int pm_type;
		int pm_time;
		int pm_flags;
		int otherFlags;
		int linkFlags;
		int bobCycle;
		float origin[3];
		float velocity[3];
		int grenadeTimeLeft;
		int throwbackGrenadeOwner;
		int throwbackGrenadeTimeLeft;
		unsigned int throwbackWeaponIndex;
		int remoteEyesEnt;
		int remoteEyesTagname;
		int remoteControlEnt;
		int foliageSoundTime;
		int gravity;
		float leanf;
		int speed;
		float delta_angles[3];
		int groundEntityNum;
		float vLadderVec[3];
		int jumpTime;
		float jumpOriginZ;
		int legsTimer;
		int legsAnim;
		int torsoTimer;
		int torsoAnim;
		int legsAnimDuration;
		int torsoAnimDuration;
		int damageTimer;
		int damageDuration;
		int flinchYawAnim;
		int corpseIndex;
		int movementDir;
		int eFlags;
		int eventSequence;
		int events[4];
		unsigned int eventParms[4];
		int oldEventSequence;
		int unpredictableEventSequence;
		int unpredictableEventSequenceOld;
		int unpredictableEvents[4];
		unsigned int unpredictableEventParms[4];
		int clientNum; // 260
		int viewmodelIndex;
		float viewangles[3];
		int viewHeightTarget;
		float viewHeightCurrent;
		int viewHeightLerpTime;
		int viewHeightLerpTarget;
		int viewHeightLerpDown;
		float viewAngleClampBase[2];
		float viewAngleClampRange[2];
		int damageEvent;
		int damageYaw;
		int damagePitch;
		int damageCount;
		int damageFlags;
		int stats[4];
		float proneDirection;
		float proneDirectionPitch;
		float proneTorsoPitch;
		ViewLockTypes viewlocked;
		int viewlocked_entNum;
		float linkAngles[3];
		float linkWeaponAngles[3];
		int linkWeaponEnt;
		int loopSound;
		int cursorHint;
		int cursorHintString;
		int cursorHintEntIndex;
		int cursorHintDualWield;
		int iCompassPlayerInfo;
		int radarEnabled;
		int radarBlocked;
		int radarMode;
		int locationSelectionInfo;
		SprintState sprintState;
		float holdBreathScale;
		int holdBreathTimer;
		float moveSpeedScaleMultiplier;
		MantleState mantleState;
		PlayerActiveWeaponState weapState[2];
		unsigned int weaponsEquipped[15];
		PlayerEquippedWeaponState weapEquippedData[15];
		PlayerWeaponCommonState weapCommon;
		float meleeChargeYaw;
		int meleeChargeDist;
		int meleeChargeTime;
		unsigned int perks[2];
		unsigned int perkSlots[8];
		ActionSlotType actionSlotType[4];
		ActionSlotParam actionSlotParam[4];
		int weaponHudIconOverrides[6];
		int animScriptedType;
		int shellshockIndex;
		int shellshockTime;
		int shellshockDuration;
		float dofNearStart;
		float dofNearEnd;
		float dofFarStart;
		float dofFarEnd;
		float dofNearBlur;
		float dofFarBlur;
		float dofViewmodelStart;
		float dofViewmodelEnd;
		objective_t objective[32];
		int deltaTime;
		int killCamEntity;
		int killCamLookAtEntity;
		int killCamClientNum;
		struct
		{
			hudelem_s current[31];
			hudelem_s archival[31];
		} hud;
		unsigned int partBits[6];
		int recoilScale;
		int diveDirection;
		int stunTime;
	};

	static_assert(sizeof(playerState_s) == 0x311C); // Confirmed

	enum LocSelInputState
	{
		LOC_SEL_INPUT_NONE = 0x0,
		LOC_SEL_INPUT_CONFIRM = 0x1,
		LOC_SEL_INPUT_CANCEL = 0x2,
	};

	struct field_t
	{
		int cursor;
		int scroll;
		int drawWidth;
		int widthInPixels;
		float charHeight;
		int fixedSize;
		char buffer[256];
	};

	struct KeyState
	{
		int down;
		int repeats;
		const char* binding;
	};

	struct PlayerKeyState
	{
		field_t chatField;
		int chat_team;
		int overstrikeMode;
		int anyKeyDown;
		KeyState keys[256];
		LocSelInputState locSelInputState;
	};

	struct keyname_t
	{
		const char* name;
		int keynum;
	};

	struct clSnapshot_t
	{
		playerState_s ps;
		int valid;
		int snapFlags;
		int serverTime;
		int messageNum;
		int deltaNum;
		int ping;
		int cmdNum;
		int numEntities;
		int numClients;
		int parseEntitiesIndex;
		int parseClientsIndex;
		int serverCommandNum;
	};

	static_assert(sizeof(clSnapshot_t) == 0x314C);

	enum StanceState
	{
		CL_STANCE_STAND = 0x0,
		CL_STANCE_CROUCH = 0x1,
		CL_STANCE_PRONE = 0x2,
	};

	struct ClientArchiveData
	{
		int serverTime;
		float origin[3];
		float velocity[3];
		int bobCycle;
		int movementDir;
		float viewangles[3];
		int locationSelectionInfo;
		float selectedLocation[2];
		float selectedLocationAngle;
	};

	struct outPacket_t
	{
		int p_cmdNumber;
		int p_serverTime;
		int p_realtime;
	};

	enum team_t
	{
		TEAM_FREE = 0x0,
		TEAM_AXIS = 0x1,
		TEAM_ALLIES = 0x2,
		TEAM_SPECTATOR = 0x3,
		TEAM_NUM_TEAMS = 0x4,
	};

	struct clientState_s
	{
		int clientIndex;
		team_t team;
		int modelindex;
		int dualWielding;
		int riotShieldNext;
		int attachModelIndex[6];
		int attachTagIndex[6];
		char name[16];
		float maxSprintTimeMultiplier;
		int rank;
		int prestige;
		unsigned int perks[2];
		int diveState;
		int voiceConnectivityBits;
		unsigned int playerCardIcon;
		unsigned int playerCardTitle;
		unsigned int playerCardNameplate;
	};

	static_assert(sizeof(clientState_s) == 0x7C);

	enum PlayerCardClientLookupType
	{
		PLAYERCARD_LOOKUP_SCRIPTSLOT = 0x0,
		PLAYERCARD_LOOKUP_LIVEPROFILE_CLIENT = 0x1,
		PLAYERCARD_LOOKUP_LIVEPROFILE_CONTROLLER = 0x2,
		PLAYERCARD_LOOKUP_LOBBY = 0x3,
		PLAYERCARD_LOOKUP_MYTEAM = 0x4,
		PLAYERCARD_LOOKUP_ENEMYTEAM = 0x5,
		PLAYERCARD_LOOKUP_COUNT = 0x6,
	};

	struct PlayerCardData
	{
		unsigned int lastUpdateTime;
		unsigned int titleIndex;
		unsigned int iconIndex;
		unsigned int nameplateIndex;
		int rank;
		int prestige;
		team_t team;
		char name[32];
		char clanAbbrev[5];
	};

	static_assert(sizeof(PlayerCardData) == 0x44);

	enum usercmdButtonBits
	{
		CMD_BUTTON_ATTACK = 1 << 0,
		CMD_BUTTON_SPRINT = 1 << 1,
		CMD_BUTTON_MELEE = 1 << 2,
		CMD_BUTTON_ACTIVATE = 1 << 3,
		CMD_BUTTON_RELOAD = 1 << 4,
		CMD_BUTTON_USE_RELOAD = 1 << 5,
		CMD_BUTTON_LEAN_LEFT = 1 << 6,
		CMD_BUTTON_LEAN_RIGHT = 1 << 7,
		CMD_BUTTON_PRONE = 1 << 8,
		CMD_BUTTON_CROUCH = 1 << 9,
		CMD_BUTTON_UP = 1 << 10,
		CMD_BUTTON_ADS = 1 << 11,
		CMD_BUTTON_DOWN = 1 << 12,
		CMD_BUTTON_BREATH = 1 << 13,
		CMD_BUTTON_FRAG = 1 << 14,
		CMD_BUTTON_OFFHAND_SECONDARY = 1 << 15,
		CMD_BUTTON_THROW = 1 << 19,
		CMD_BUTTON_REMOTE = 1 << 20,
	};

	struct usercmd_s
	{
		int serverTime;
		int buttons;
		int angles[3];
		unsigned __int16 weapon;
		unsigned __int16 primaryWeaponForAltMode;
		unsigned __int16 offHandIndex;
		char forwardmove;
		char rightmove;
		float meleeChargeYaw;
		char meleeChargeDist;
		char selectedLoc[2];
		char selectedLocAngle;
		char remoteControlAngles[2];
	};

	static_assert(sizeof(usercmd_s) == 0x28);

	enum trType_t
	{
		TR_STATIONARY = 0x0,
		TR_INTERPOLATE = 0x1,
		TR_LINEAR = 0x2,
		TR_LINEAR_STOP = 0x3,
		TR_SINE = 0x4,
		TR_GRAVITY = 0x5,
		TR_LOW_GRAVITY = 0x6,
		TR_ACCELERATE = 0x7,
		TR_DECELERATE = 0x8,
		TR_PHYSICS = 0x9,
		TR_FIRST_RAGDOLL = 0xA,
		TR_RAGDOLL = 0xA,
		TR_RAGDOLL_GRAVITY = 0xB,
		TR_RAGDOLL_INTERPOLATE = 0xC,
		TR_LAST_RAGDOLL = 0xC,
		NUM_TRTYPES = 0xD,
	};

	struct trajectory_t
	{
		trType_t trType;
		int trTime;
		int trDuration;
		float trBase[3];
		float trDelta[3];
	};

	struct LerpEntityStateTurret
	{
		float gunAngles[3];
		int lastBarrelRotChangeTime;
		int lastBarrelRotChangeRate;
		int lastHeatChangeLevel;
		int lastHeatChangeTime;
		bool isBarrelRotating;
		bool isOverheat;
		bool isHeatingUp;
		bool isBeingCarried;
	};

	union LerpEntityStateTypeUnion
	{
		LerpEntityStateTurret turret;
		char pad0[0x24];
	};

	static_assert(sizeof(LerpEntityStateTypeUnion) == 0x24);

	struct LerpEntityState
	{
		int eFlags;
		trajectory_t pos;
		trajectory_t apos;
		LerpEntityStateTypeUnion u;
	};

	static_assert(sizeof(LerpEntityState) == 0x70);

	struct clientLinkInfo_t
	{
		__int16 parentId;
		char tagName;
		char flags;
	};

	struct entityState_s
	{
		int number;
		int eType;
		LerpEntityState lerp;
		int time2;
		int otherEntityNum;
		int attackerEntityNum;
		int groundEntityNum;
		int loopSound;
		int surfType;
		union
		{
			int brushModel;
			int triggerModel;
			int item;
			int xmodel;
			int primaryLight;
		} index;
		int clientNum;
		int iHeadIcon;
		int iHeadIconTeam;
		int solid;
		unsigned int eventParm;
		int eventSequence;
		int events[4];
		unsigned int eventParms[4];
		unsigned __int16 weapon;
		int legsAnim;
		int torsoAnim;
		union
		{
			int eventParm2;
			int hintString;
			int fxId;
			int helicopterStage;
		} un1;
		union
		{
			int hintType;
			struct
			{
				unsigned __int16 vehicleXModel;
				char weaponModel;
			} __s1;
			int actorFlags;
		} un2;
		clientLinkInfo_t clientLinkInfo;
		unsigned int partBits[6];
		int clientMask[1];
	};

	struct clientActive_t
	{
		bool usingAds;
		int timeoutcount;
		clSnapshot_t snap;
		bool alwaysFalse;
		int serverTime;
		int oldServerTime;
		int oldFrameServerTime;
		int serverTimeDelta;
		int oldSnapServerTime;
		int extrapolatedSnapshot;
		int newSnapshots;
		int serverId;
		char mapname[MAX_QPATH];
		int parseEntitiesIndex;
		int parseClientsIndex;
		int mouseDx[2];
		int mouseDy[2];
		int mouseIndex;
		bool stanceHeld;
		StanceState stance;
		StanceState stancePosition;
		int stanceTime;
		int cgameUserCmdWeapon;
		int cgameUserCmdOffHandIndex;
		float cgameFOVSensitivityScale;
		float cgameMaxPitchSpeed;
		float cgameMaxYawSpeed;
		float cgameKickAngles[3];
		float cgameOrigin[3];
		float cgameVelocity[3];
		float cgameViewangles[3];
		int cgameBobCycle;
		int cgameMovementDir;
		int cgameExtraButtons;
		int cgamePredictedDataServerTime;
		float clViewangles[3];
		usercmd_s cmds[128];
		int cmdNumber;
		ClientArchiveData clientArchive[256];
		int clientArchiveIndex;
		int packetBackupCount;
		int packetBackupMask;
		int parseEntitiesCount;
		int parseClientsCount;
		outPacket_t outPackets[32];
		clSnapshot_t snapshots[32];
		entityState_s parseEntities[19200];
		clientState_s parseClients[576];
		int corruptedTranslationFile;
		char translationVersion[256];
	};

	struct MaterialTechnique
	{
		const char* name;
		unsigned __int16 flags;
		unsigned __int16 passCount;
		MaterialPass passArray[1];
	};

	struct MaterialTechniqueSet
	{
		const char* name;
		char worldVertFormat;
		bool hasBeenUploaded;
		char unused[1];
		MaterialTechniqueSet* remappedTechniqueSet;
		MaterialTechnique* techniques[48];
	};

	struct GfxImageLoadDefIW3
	{
		char levelCount;
		char flags;
		__int16 dimensions[3];
		int format;
		int resourceSize;
		char data[1];
	};

	struct __declspec(align(4)) GfxImageLoadDef
	{
		char levelCount;
		char pad[3];
		int flags;
		int format;
		int resourceSize;
		unsigned char data[1];
	};

	union GfxTexture
	{
		IDirect3DBaseTexture9* basemap;
		IDirect3DTexture9* map;
		IDirect3DVolumeTexture9* volmap;
		IDirect3DCubeTexture9* cubemap;
		GfxImageLoadDef* loadDef;
	};

	struct Picmip
	{
		char platform[2];
	};

	struct CardMemory
	{
		int platform[2];
	};

	struct GfxImage
	{
		GfxTexture texture;
		char mapType;
		TextureSemantic semantic;
		char category;
		bool useSrgbReads;
		Picmip picmip;
		bool noPicmip;
		char track;
		CardMemory cardMemory;
		unsigned __int16 width;
		unsigned __int16 height;
		unsigned __int16 depth;
		bool delayLoadPixels;
		const char* name;
	};

	struct WaterWritable
	{
		float floatTime;
	};

	struct complex_s
	{
		float real;
		float imag;
	};

	struct water_t
	{
		WaterWritable writable;
		complex_s* H0;
		float* wTerm;
		int M;
		int N;
		float Lx;
		float Lz;
		float gravity;
		float windvel;
		float winddir[2];
		float amplitude;
		float codeConstant[4];
		GfxImage* image;
	};

	union MaterialTextureDefInfo
	{
		GfxImage* image;
		water_t* water;
	};

	struct MaterialTextureDef
	{
		unsigned int nameHash;
		char nameStart;
		char nameEnd;
		char samplerState;
		TextureSemantic semantic;
		MaterialTextureDefInfo u;
	};

	struct MaterialConstantDef
	{
		unsigned int nameHash;
		char name[12];
		float literal[4];
	};

	enum GfxSurfaceStatebitOp0 : unsigned int
	{
		GFXS0_SRCBLEND_RGB_SHIFT = 0x0,
		GFXS0_SRCBLEND_RGB_MASK = 0xF,
		GFXS0_DSTBLEND_RGB_SHIFT = 0x4,
		GFXS0_DSTBLEND_RGB_MASK = 0xF0,
		GFXS0_BLENDOP_RGB_SHIFT = 0x8,
		GFXS0_BLENDOP_RGB_MASK = 0x700,
		GFXS0_BLEND_RGB_MASK = 0x7FF,
		GFXS0_ATEST_DISABLE = 0x800,
		GFXS0_ATEST_GT_0 = 0x1000,
		GFXS0_ATEST_LT_128 = 0x2000,
		GFXS0_ATEST_GE_128 = 0x3000,
		GFXS0_ATEST_MASK = 0x3000,
		GFXS0_CULL_SHIFT = 0xE,
		GFXS0_CULL_NONE = 0x4000,
		GFXS0_CULL_BACK = 0x8000,
		GFXS0_CULL_FRONT = 0xC000,
		GFXS0_CULL_MASK = 0xC000,
		GFXS0_SRCBLEND_ALPHA_SHIFT = 0x10,
		GFXS0_SRCBLEND_ALPHA_MASK = 0xF0000,
		GFXS0_DSTBLEND_ALPHA_SHIFT = 0x14,
		GFXS0_DSTBLEND_ALPHA_MASK = 0xF00000,
		GFXS0_BLENDOP_ALPHA_SHIFT = 0x18,
		GFXS0_BLENDOP_ALPHA_MASK = 0x7000000,
		GFXS0_BLEND_ALPHA_MASK = 0x7FF0000,
		GFXS0_COLORWRITE_RGB = 0x8000000,
		GFXS0_COLORWRITE_ALPHA = 0x10000000,
		GFXS0_COLORWRITE_MASK = 0x18000000,
		GFXS0_GAMMAWRITE = 0x40000000,
		GFXS0_POLYMODE_LINE = 0x80000000
	};

	enum GfxSurfaceStatebitOp1 : unsigned int
	{
		GFXS1_DEPTHWRITE = 0x1,
		GFXS1_DEPTHTEST_DISABLE = 0x2,
		GFXS1_DEPTHTEST_SHIFT = 0x2,
		GFXS1_DEPTHTEST_ALWAYS = 0x0,
		GFXS1_DEPTHTEST_LESS = 0x4,
		GFXS1_DEPTHTEST_EQUAL = 0x8,
		GFXS1_DEPTHTEST_LESSEQUAL = 0xC,
		GFXS1_DEPTHTEST_MASK = 0xC,
		GFXS1_POLYGON_OFFSET_SHIFT = 0x4,
		GFXS1_POLYGON_OFFSET_0 = 0x0,
		GFXS1_POLYGON_OFFSET_1 = 0x10,
		GFXS1_POLYGON_OFFSET_2 = 0x20,
		GFXS1_POLYGON_OFFSET_SHADOWMAP = 0x30,
		GFXS1_POLYGON_OFFSET_MASK = 0x30,
		GFXS1_STENCIL_FRONT_ENABLE = 0x40,
		GFXS1_STENCIL_BACK_ENABLE = 0x80,
		GFXS1_STENCIL_MASK = 0xC0,
		GFXS1_STENCIL_FRONT_PASS_SHIFT = 0x8,
		GFXS1_STENCIL_FRONT_FAIL_SHIFT = 0xB,
		GFXS1_STENCIL_FRONT_ZFAIL_SHIFT = 0xE,
		GFXS1_STENCIL_FRONT_FUNC_SHIFT = 0x11,
		GFXS1_STENCIL_FRONT_MASK = 0xFFF00,
		GFXS1_STENCIL_BACK_PASS_SHIFT = 0x14,
		GFXS1_STENCIL_BACK_FAIL_SHIFT = 0x17,
		GFXS1_STENCIL_BACK_ZFAIL_SHIFT = 0x1A,
		GFXS1_STENCIL_BACK_FUNC_SHIFT = 0x1D,
		GFXS1_STENCIL_BACK_MASK = 0xFFF00000,
		GFXS1_STENCILFUNC_FRONTBACK_MASK = 0xE00E0000,
		GFXS1_STENCILOP_FRONTBACK_MASK = 0x1FF1FF00,
	};

	enum GfxStencilOp
	{
		GFXS_STENCILOP_KEEP = 0x0,
		GFXS_STENCILOP_ZERO = 0x1,
		GFXS_STENCILOP_REPLACE = 0x2,
		GFXS_STENCILOP_INCRSAT = 0x3,
		GFXS_STENCILOP_DECRSAT = 0x4,
		GFXS_STENCILOP_INVERT = 0x5,
		GFXS_STENCILOP_INCR = 0x6,
		GFXS_STENCILOP_DECR = 0x7,

		GFXS_STENCILOP_COUNT,
		GFXS_STENCILOP_MASK = 0x7
	};

	struct GfxStateBits
	{
		unsigned int loadBits[2];
	};

	struct Material
	{
		MaterialInfo info;
		char stateBitsEntry[48];
		unsigned char textureCount;
		unsigned char constantCount;
		unsigned char stateBitsCount;
		char stateFlags;
		char cameraRegion;
		MaterialTechniqueSet* techniqueSet;
		MaterialTextureDef* textureTable;
		MaterialConstantDef* constantTable;
		GfxStateBits* stateBitsTable;
	};

	struct XModelLodInfo
	{
		float dist;
		unsigned __int16 numsurfs;
		unsigned __int16 surfIndex;
		XModelSurfs* modelSurfs;
		int partBits[6];
		XSurface* surfs;
		char lod;
		char smcBaseIndexPlusOne;
		char smcSubIndexMask;
		char smcBucket;
	};

	struct XModelCollTri_s
	{
		float plane[4];
		float svec[4];
		float tvec[4];
	};

	struct XModelCollSurf_s
	{
		XModelCollTri_s* collTris;
		int numCollTris;
		Bounds bounds;
		int boneIdx;
		int contents;
		int surfFlags;
	};

	struct XBoneInfo
	{
		Bounds bounds;
		float radiusSquared;
	};

	struct XModel
	{
		const char* name;
		unsigned char numBones;
		unsigned char numRootBones;
		unsigned char numsurfs;
		unsigned char lodRampType;
		float scale;
		unsigned int noScalePartBits[6];
		unsigned __int16* boneNames;
		unsigned char* parentList;
		short* quats;
		float* trans;
		unsigned char* partClassification;
		DObjAnimMat* baseMat;
		Material** materialHandles;
		XModelLodInfo lodInfo[4];
		unsigned char maxLoadedLod;
		unsigned char numLods;
		unsigned char collLod;
		unsigned char flags;
		XModelCollSurf_s* collSurfs;
		int numCollSurfs;
		int contents;
		XBoneInfo* boneInfo;
		float radius;
		Bounds bounds;
		int memUsage;
		bool bad;
		PhysPreset* physPreset;
		PhysCollmap* physCollmap;
	};

	struct _AILSOUNDINFO
	{
		int format;
		const void* data_ptr;
		unsigned int data_len;
		unsigned int rate;
		int bits;
		int channels;
		unsigned int samples;
		unsigned int block_size;
		const void* initial_ptr;
	};

	struct MssSound
	{
		_AILSOUNDINFO info;
		char* data;
	};

	struct LoadedSound
	{
		const char* name;
		MssSound sound;
	};

	struct StreamFileNameRaw
	{
		const char* dir;
		const char* name;
	};

	union StreamFileInfo
	{
		StreamFileNameRaw raw;
	};

	struct StreamFileName
	{
		StreamFileInfo info;
	};

	struct StreamedSound
	{
		StreamFileName filename;
	};

	union SoundFileRef
	{
		LoadedSound* loadSnd;
		StreamedSound streamSnd;
	};

	enum snd_alias_type_t
	{
		SAT_UNKNOWN = 0x0,
		SAT_LOADED = 0x1,
		SAT_STREAMED = 0x2,
		SAT_VOICED = 0x3,
		SAT_COUNT = 0x4,
	};

	struct snd_volume_info_t
	{
		float volume;
		float goalvolume;
		float goalrate;
	};

	struct snd_channelvolgroup
	{
		snd_volume_info_t channelvol[64];
		bool active;
	};

	struct snd_background_info_t
	{
		float goalvolume;
		float goalrate;
	};

	struct snd_enveffect
	{
		int roomtype;
		float drylevel;
		float drygoal;
		float dryrate;
		float wetlevel;
		float wetgoal;
		float wetrate;
		bool active;
	};

	struct orientation_t
	{
		float origin[3];
		float axis[3][3];
	};

	struct snd_listener
	{
		orientation_t orient;
		float velocity;
		int clientNum;
		bool active;
	};

	struct snd_amplifier
	{
		snd_listener* listener;
		int minRadius;
		int maxRadius;
		float falloffExp;
		float minVol;
		float maxVol;
	};

	struct snd_entchannel_info_t
	{
		char name[64];
		int priority;
		bool is3d;
		bool isRestricted;
		bool isPausable;
		int maxVoices;
		int voiceCount;
	};

	struct snd_entchan_overrides_t
	{
		unsigned int isPausable[2];
		float timescaleLerp[64];
	};

	enum SndFileLoadingState
	{
		SFLS_UNLOADED = 0x0,
		SFLS_LOADING = 0x1,
		SFLS_LOADED = 0x2,
	};

	struct SndFileSpecificChannelInfo
	{
		SndFileLoadingState loadingState;
		int srcChannelCount;
		int baserate;
	};

	union SndEntHandle
	{
		struct
		{
			unsigned int entIndex;
		} field;
		int handle;
	};

	enum SndLengthId
	{
		SndLengthNotify_Subtitle = 0x0,
		SndLengthNotify_EntityCustom = 0x1,
		SndLengthNotifyCount = 0x2,
	};

	struct sndLengthNotifyInfo
	{
		SndLengthId id[4];
		void* data[4];
		int count;
	};

	enum snd_alias_system_t
	{
		SASYS_UI = 0x0,
		SASYS_CGAME = 0x1,
		SASYS_GAME = 0x2,
		SASYS_COUNT = 0x3,
	};

	struct SoundFile
	{
		char type;
		char exists;
		SoundFileRef u;
	};

	struct MSSSpeakerLevels
	{
		int speaker;
		int numLevels;
		float levels[2];
	};

	struct MSSChannelMap
	{
		unsigned int speakerCount;
		MSSSpeakerLevels speakers[6];
	};

	struct SpeakerMap
	{
		bool isDefault;
		const char* name;
		MSSChannelMap channelMaps[2][2];
	};

	union SoundAliasFlags
	{
#pragma warning(push)
#pragma warning(disable: 4201)
		struct
		{
			unsigned int looping : 1;		// & 1	/ 0x1			/ 0000 0000 0000 0001
			unsigned int isMaster : 1;		// & 2	/ 0x2			/ 0000 0000 0000 0010
			unsigned int isSlave : 1;		// & 4	/ 0x4			/ 0000 0000 0000 0100
			unsigned int fullDryLevel : 1;	//	& 8	/ 0x8			/ 0000 0000 0000 1000
			unsigned int noWetLevel : 1;	// & 16	/ 0x10			/ 0000 0000 0001 0000
			unsigned int unknown : 1;		// & 32	/ 0x20			/ 0000 0000 0010 0000
			unsigned int unk_is3D : 1;		// & 64	/ 0x40			/ 0000 0000 0100 0000		// CONFIRMED IW4 IW5
			unsigned int type : 2;			// & 384	/ 0x180		/ 0000 0001 1000 0000		// CONFIRMED IW4 IW5
			unsigned int channel : 6;		// & 32256	/ 0x7E00	/ 0111 1110 0000 0000		// CONFIRMED IW4 IW5
		};
#pragma warning(pop)
		unsigned int intValue;
	};

	struct SndCurve
	{
		const char* filename;
		unsigned __int16 knotCount;
		float knots[16][2];
	};

	struct snd_alias_t
	{
		const char* aliasName;
		const char* subtitle;
		const char* secondaryAliasName;
		const char* chainAliasName;
		const char* mixerGroup;
		SoundFile* soundFile;
		int sequence;
		float volMin;
		float volMax;
		float pitchMin;
		float pitchMax;
		float distMin;
		float distMax;
		float velocityMin;
		SoundAliasFlags flags;
		union
		{
			float slavePercentage;
			float masterPercentage;
		} ___u15;
		float probability;
		float lfePercentage;
		float centerPercentage;
		int startDelay;
		SndCurve* volumeFalloffCurve;
		float envelopMin;
		float envelopMax;
		float envelopPercentage;
		SpeakerMap* speakerMap;
	};

	struct snd_channel_info_t
	{
		SndFileSpecificChannelInfo soundFileInfo;
		SndEntHandle sndEnt;
		int entchannel;
		int startDelay;
		int looptime;
		int totalMsec;
		int playbackId;
		sndLengthNotifyInfo lengthNotifyInfo;
		float basevolume;
		float pitch;
		snd_alias_t* alias0;
		snd_alias_t* alias1;
		int saveIndex0;
		int saveIndex1;
		float lerp;
		float org[3];
		float offset[3];
		bool paused;
		bool master;
		float timescaleLerp;
		snd_alias_system_t system;
	};

	struct snd_local_t
	{
		bool Initialized2d;
		bool Initialized3d;
		bool paused;
		int playbackIdCounter;
		unsigned int playback_rate;
		int playback_channels;
		float timescale;
		int pausetime;
		int cpu;
		struct
		{
			char buffer[16384];
			volatile int size;
			bool compress;
		} restore;
		float volume;
		snd_volume_info_t mastervol;
		snd_channelvolgroup channelVolGroups[4];
		snd_channelvolgroup* channelvol;
		snd_background_info_t background[4];
		int ambient_track;
		float slaveLerp;
		float masterPercentage;
		snd_enveffect envEffects[5];
		snd_enveffect* effect;
		snd_listener listeners[2];
		int time;
		int looptime;
		snd_amplifier amplifier;
		snd_entchannel_info_t entchaninfo[64];
		snd_entchan_overrides_t entchanOverrides;
		int entchannel_count;
		snd_channel_info_t chaninfo[52];
		int max_2D_channels;
		int max_3D_channels;
		int max_stream_channels;
	};

	struct Poly
	{
		float(*pts)[3];
		unsigned int ptCount;
	};

	enum SunShadowPartition
	{
		R_SUNSHADOW_NEAR = 0x0,
		R_SUNSHADOW_FAR = 0x1,
		R_SUNSHADOW_PARTITION_COUNT = 0x2,
	};

	struct snd_alias_list_t
	{
		const char* aliasName;
		snd_alias_t* head;
		unsigned int count;
	};

	struct cStaticModel_s
	{
		XModel* xmodel;
		float origin[3];
		float invScaledAxis[3][3];
		Bounds absBounds;
	};

	struct ClipMaterial
	{
		const char* name;
		int surfaceFlags;
		int contents;
	};

	struct cNode_t
	{
		cplane_s* plane;
		__int16 children[2];
	};

	struct cLeaf_t
	{
		unsigned __int16 firstCollAabbIndex;
		unsigned __int16 collAabbCount;
		int brushContents;
		int terrainContents;
		Bounds bounds;
		int leafBrushNode;
	};

	struct cLeafBrushNodeLeaf_t
	{
		unsigned __int16* brushes;
	};

	struct cLeafBrushNodeChildren_t
	{
		float dist;
		float range;
		unsigned __int16 childOffset[2];
	};

	union cLeafBrushNodeData_t
	{
		cLeafBrushNodeLeaf_t leaf;
		cLeafBrushNodeChildren_t children;
	};

	struct cLeafBrushNode_s
	{
		unsigned char axis;
		__int16 leafBrushCount;
		int contents;
		cLeafBrushNodeData_t data;
	};

	struct CollisionBorder
	{
		float distEq[3];
		float zBase;
		float zSlope;
		float start;
		float length;
	};

	struct CollisionPartition
	{
		unsigned char triCount;
		unsigned char borderCount;
		unsigned char firstVertSegment;
		int firstTri;
		CollisionBorder* borders;
	};

	union CollisionAabbTreeIndex
	{
		int firstChildIndex;
		int partitionIndex;
	};

	struct CollisionAabbTree
	{
		float midPoint[3];
		unsigned __int16 materialIndex;
		unsigned __int16 childCount;
		float halfSize[3];
		CollisionAabbTreeIndex u;
	};

	struct cmodel_t
	{
		Bounds bounds;
		float radius;
		cLeaf_t leaf;
	};

	static_assert(sizeof(cmodel_t) == 0x44);

	struct TriggerModel
	{
		int contents;
		unsigned __int16 hullCount;
		unsigned __int16 firstHull;
	};

	struct TriggerHull
	{
		Bounds bounds;
		int contents;
		unsigned __int16 slabCount;
		unsigned __int16 firstSlab;
	};

	struct TriggerSlab
	{
		float dir[3];
		float midPoint;
		float halfSize;
	};

	struct MapTriggers
	{
		unsigned int count;
		TriggerModel* models;
		unsigned int hullCount;
		TriggerHull* hulls;
		unsigned int slabCount;
		TriggerSlab* slabs;
	};

	struct Stage
	{
		const char* name;
		float origin[3];
		unsigned __int16 triggerIndex;
		char sunPrimaryLightIndex;
	};

	struct __declspec(align(4)) MapEnts
	{
		const char* name;
		const char* entityString;
		int numEntityChars;
		MapTriggers trigger;
		Stage* stages;
		char stageCount;
	};

	struct SModelAabbNode
	{
		Bounds bounds;
		unsigned __int16 firstChild;
		unsigned __int16 childCount;
	};

	enum DynEntityType
	{
		DYNENT_TYPE_INVALID = 0x0,
		DYNENT_TYPE_CLUTTER = 0x1,
		DYNENT_TYPE_DESTRUCT = 0x2,
		DYNENT_TYPE_COUNT = 0x3,
	};

	struct GfxPlacement
	{
		float quat[4];
		float origin[3];
	};

	struct FxSpawnDefLooping
	{
		int intervalMsec;
		int count;
	};

	struct FxIntRange
	{
		int base;
		int amplitude;
	};

	struct FxSpawnDefOneShot
	{
		FxIntRange count;
	};

	union FxSpawnDef
	{
		FxSpawnDefLooping looping;
		FxSpawnDefOneShot oneShot;
	};

	struct FxFloatRange
	{
		float base;
		float amplitude;
	};

	struct FxElemAtlas
	{
		char behavior;
		char index;
		char fps;
		char loopCount;
		char colIndexBits;
		char rowIndexBits;
		__int16 entryCount;
	};

	struct FxElemVec3Range
	{
		float base[3];
		float amplitude[3];
	};

	struct FxElemVelStateInFrame
	{
		FxElemVec3Range velocity;
		FxElemVec3Range totalDelta;
	};

	const struct FxElemVelStateSample
	{
		FxElemVelStateInFrame local;
		FxElemVelStateInFrame world;
	};

	struct FxElemVisualState
	{
		unsigned char color[4];
		float rotationDelta;
		float rotationTotal;
		float size[2];
		float scale;
	};

	const struct FxElemVisStateSample
	{
		FxElemVisualState base;
		FxElemVisualState amplitude;
	};

	struct FxElemMarkVisuals
	{
		Material* materials[2];
	};

	union FxEffectDefRef
	{
		FxEffectDef* handle;
		const char* name;
	};

	union FxElemVisuals
	{
		const void* anonymous;
		Material* material;
		XModel* model;
		FxEffectDefRef effectDef;
		const char* soundName;
	};

	union FxElemDefVisuals
	{
		FxElemMarkVisuals* markArray;
		FxElemVisuals* array;
		FxElemVisuals instance;
	};

	struct FxTrailVertex
	{
		float pos[2];
		float normal[2];
		float texCoord;
	};

	struct FxTrailDef
	{
		int scrollTimeMsec;
		int repeatDist;
		float invSplitDist;
		float invSplitArcDist;
		float invSplitTime;
		int vertCount;
		FxTrailVertex* verts;
		int indCount;
		unsigned __int16* inds;
	};

	struct FxSparkFountainDef
	{
		float gravity;
		float bounceFrac;
		float bounceRand;
		float sparkSpacing;
		float sparkLength;
		int sparkCount;
		float loopTime;
		float velMin;
		float velMax;
		float velConeFrac;
		float restSpeed;
		float boostTime;
		float boostFactor;
	};

	union FxElemExtendedDefPtr
	{
		FxTrailDef* trailDef;
		FxSparkFountainDef* sparkFountainDef;
		void* unknownDef;
	};

	const struct FxElemDef
	{
		int flags;
		FxSpawnDef spawn;
		FxFloatRange spawnRange;
		FxFloatRange fadeInRange;
		FxFloatRange fadeOutRange;
		float spawnFrustumCullRadius;
		FxIntRange spawnDelayMsec;
		FxIntRange lifeSpanMsec;
		FxFloatRange spawnOrigin[3];
		FxFloatRange spawnOffsetRadius;
		FxFloatRange spawnOffsetHeight;
		FxFloatRange spawnAngles[3];
		FxFloatRange angularVelocity[3];
		FxFloatRange initialRotation;
		FxFloatRange gravity;
		FxFloatRange reflectionFactor;
		FxElemAtlas atlas;
		char elemType;
		char visualCount;
		char velIntervalCount;
		char visStateIntervalCount;
		FxElemVelStateSample* velSamples;
		FxElemVisStateSample* visSamples;
		FxElemDefVisuals visuals;
		Bounds collBounds;
		FxEffectDefRef effectOnImpact;
		FxEffectDefRef effectOnDeath;
		FxEffectDefRef effectEmitted;
		FxFloatRange emitDist;
		FxFloatRange emitDistVariance;
		FxElemExtendedDefPtr extended;
		char sortOrder;
		char lightingFrac;
		char useItemClip;
		char fadeInfo;
	};

	struct FxEffectDef
	{
		const char* name;
		int flags;
		int totalSize;
		int msecLoopingLife;
		int elemDefCountLooping;
		int elemDefCountOneShot;
		int elemDefCountEmission;
		FxElemDef* elemDefs;
	};

	struct DynEntityDef
	{
		DynEntityType type;
		GfxPlacement pose;
		XModel* xModel;
		unsigned __int16 brushModel;
		unsigned __int16 physicsBrushModel;
		FxEffectDef* destroyFx;
		PhysPreset* physPreset;
		int health;
		PhysMass mass;
		int contents;
	};

	struct DynEntityPose
	{
		GfxPlacement pose;
		float radius;
	};

	struct DynEntityClient
	{
		int physObjId;
		unsigned __int16 flags;
		unsigned __int16 lightingHandle;
		int health;
	};

	struct DynEntityColl
	{
		unsigned __int16 sector;
		unsigned __int16 nextEntInSector;
		float linkMins[2];
		float linkMaxs[2];
	};

#pragma warning(push)
#pragma warning(disable: 4324)
	struct __declspec(align(64)) clipMap_t
	{
		const char* name;
		int isInUse;
		unsigned int planeCount;
		cplane_s* planes;
		unsigned int numStaticModels;
		cStaticModel_s* staticModelList;
		unsigned int numMaterials;
		ClipMaterial* materials;
		unsigned int numBrushSides;
		cbrushside_t* brushsides;
		unsigned int numBrushEdges;
		unsigned char* brushEdges;
		unsigned int numNodes;
		cNode_t* nodes;
		unsigned int numLeafs;
		cLeaf_t* leafs;
		unsigned int leafbrushNodesCount;
		cLeafBrushNode_s* leafbrushNodes;
		unsigned int numLeafBrushes;
		unsigned __int16* leafbrushes;
		unsigned int numLeafSurfaces;
		unsigned int* leafsurfaces;
		unsigned int vertCount;
		vec3_t* verts;
		unsigned int triCount;
		unsigned __int16* triIndices;
		unsigned char* triEdgeIsWalkable;
		unsigned int borderCount;
		CollisionBorder* borders;
		unsigned int partitionCount;
		CollisionPartition* partitions;
		unsigned int aabbTreeCount;
		CollisionAabbTree* aabbTrees;
		unsigned int numSubModels;
		cmodel_t* cmodels;
		unsigned __int16 numBrushes;
		cbrush_t* brushes;
		Bounds* brushBounds;
		int* brushContents;
		MapEnts* mapEnts;
		unsigned __int16 smodelNodeCount;
		SModelAabbNode* smodelNodes;
		unsigned __int16 dynEntCount[2];
		DynEntityDef* dynEntDefList[2];
		DynEntityPose* dynEntPoseList[2];
		DynEntityClient* dynEntClientList[2];
		DynEntityColl* dynEntCollList[2];
		unsigned int checksum;
	};
#pragma warning(pop)

	struct ComPrimaryLight
	{
		char type;
		char canUseShadowMap;
		char exponent;
		char unused;
		float color[3];
		float dir[3];
		float origin[3];
		float radius;
		float cosHalfFovOuter;
		float cosHalfFovInner;
		float cosHalfFovExpanded;
		float rotationLimit;
		float translationLimit;
		const char* defName;
	};

	struct ComWorld
	{
		const char* name;
		int isInUse;
		unsigned int primaryLightCount;
		ComPrimaryLight* primaryLights;
	};

	enum nodeType
	{
		NODE_ERROR = 0x0,
		NODE_PATHNODE = 0x1,
		NODE_COVER_STAND = 0x2,
		NODE_COVER_CROUCH = 0x3,
		NODE_COVER_CROUCH_WINDOW = 0x4,
		NODE_COVER_PRONE = 0x5,
		NODE_COVER_RIGHT = 0x6,
		NODE_COVER_LEFT = 0x7,
		NODE_AMBUSH = 0x8,
		NODE_EXPOSED = 0x9,
		NODE_CONCEALMENT_STAND = 0xA,
		NODE_CONCEALMENT_CROUCH = 0xB,
		NODE_CONCEALMENT_PRONE = 0xC,
		NODE_DOOR = 0xD,
		NODE_DOOR_INTERIOR = 0xE,
		NODE_SCRIPTED = 0xF,
		NODE_NEGOTIATION_BEGIN = 0x10,
		NODE_NEGOTIATION_END = 0x11,
		NODE_TURRET = 0x12,
		NODE_GUARD = 0x13,
		NODE_NUMTYPES = 0x14,
		NODE_DONTLINK = 0x14,
	};

	enum PathNodeErrorCode
	{
		PNERR_NONE = 0x0,
		PNERR_INSOLID = 0x1,
		PNERR_FLOATING = 0x2,
		PNERR_NOLINK = 0x3,
		PNERR_DUPLICATE = 0x4,
		PNERR_NOSTANCE = 0x5,
		PNERR_INVALIDDOOR = 0x6,
		PNERR_NOANGLES = 0x7,
		PNERR_BADPLACEMENT = 0x8,
		NUM_PATH_NODE_ERRORS = 0x9,
	};

	union $23305223CFD097B6F79557BDD2047E6C
	{
		float minUseDistSq;
		PathNodeErrorCode error;
	};

	struct pathlink_s
	{
		float fDist;
		unsigned __int16 nodeNum;
		char disconnectCount;
		char negotiationLink;
		char flags;
		char ubBadPlaceCount[3];
	};

	struct pathnode_constant_t
	{
		nodeType type;
		unsigned __int16 spawnflags;
		unsigned __int16 targetname;
		unsigned __int16 script_linkName;
		unsigned __int16 script_noteworthy;
		unsigned __int16 target;
		unsigned __int16 animscript;
		int animscriptfunc;
		float vOrigin[3];
		float fAngle;
		float forward[2];
		float fRadius;
		$23305223CFD097B6F79557BDD2047E6C ___u12;
		__int16 wOverlapNode[2];
		unsigned __int16 totalLinkCount;
		pathlink_s* Links;
	};

	struct pathnode_dynamic_t
	{
		void* pOwner;
		int iFreeTime;
		int iValidTime[3];
		int dangerousNodeTime[3];
		int inPlayerLOSTime;
		__int16 wLinkCount;
		__int16 wOverlapCount;
		__int16 turretEntNumber;
		char userCount;
		bool hasBadPlaceLink;
	};

	union $73F238679C0419BE2C31C6559E8604FC
	{
		float nodeCost;
		int linkIndex;
	};

	struct pathnode_transient_t
	{
		int iSearchFrame;
		pathnode_t* pNextOpen;
		pathnode_t* pPrevOpen;
		pathnode_t* pParent;
		float fCost;
		float fHeuristic;
		$73F238679C0419BE2C31C6559E8604FC ___u6;
	};

	struct pathnode_t
	{
		pathnode_constant_t constant;
		pathnode_dynamic_t dynamic;
		pathnode_transient_t transient;
	};

	struct pathbasenode_t
	{
		float vOrigin[3];
		unsigned int type;
	};

	struct pathnode_tree_nodes_t
	{
		int nodeCount;
		unsigned __int16* nodes;
	};

	union pathnode_tree_info_t
	{
		pathnode_tree_t* child[2];
		pathnode_tree_nodes_t s;
	};

	struct pathnode_tree_t
	{
		int axis;
		float dist;
		pathnode_tree_info_t u;
	};

	struct PathData
	{
		unsigned int nodeCount;
		pathnode_t* nodes;
		pathbasenode_t* basenodes;
		unsigned int chainNodeCount;
		unsigned __int16* chainNodeForNode;
		unsigned __int16* nodeForChainNode;
		int visBytes;
		char* pathVis;
		int nodeTreeCount;
		pathnode_tree_t* nodeTree;
	};

	struct VehicleTrackObstacle
	{
		float origin[2];
		float radius;
	};

	struct VehicleTrackSector
	{
		float startEdgeDir[2];
		float startEdgeDist;
		float leftEdgeDir[2];
		float leftEdgeDist;
		float rightEdgeDir[2];
		float rightEdgeDist;
		float sectorLength;
		float sectorWidth;
		float totalPriorLength;
		float totalFollowingLength;
		VehicleTrackObstacle* obstacles;
		unsigned int obstacleCount;
	};

	struct VehicleTrackSegment
	{
		const char* targetName;
		VehicleTrackSector* sectors;
		unsigned int sectorCount;
		VehicleTrackSegment** nextBranches;
		unsigned int nextBranchesCount;
		VehicleTrackSegment** prevBranches;
		unsigned int prevBranchesCount;
		float endEdgeDir[2];
		float endEdgeDist;
		float totalLength;
	};

	struct VehicleTrack
	{
		VehicleTrackSegment* segments;
		unsigned int segmentCount;
	};

	struct G_GlassPiece
	{
		unsigned __int16 damageTaken;
		unsigned __int16 collapseTime;
		int lastStateChangeTime;
		char impactDir;
		char impactPos[2];
	};

	struct G_GlassName
	{
		char* nameStr;
		unsigned __int16 name;
		unsigned __int16 pieceCount;
		unsigned __int16* pieceIndices;
	};

	struct G_GlassData
	{
		G_GlassPiece* glassPieces;
		unsigned int pieceCount;
		unsigned __int16 damageToWeaken;
		unsigned __int16 damageToDestroy;
		unsigned int glassNameCount;
		G_GlassName* glassNames;
		char pad[108];
	};

	struct GameWorldSp
	{
		const char* name;
		PathData path;
		VehicleTrack vehicleTrack;
		G_GlassData* g_glassData;
	};

	struct GameWorldMp
	{
		const char* name;
		G_GlassData* g_glassData;
	};

	struct FxGlassDef
	{
		float halfThickness;
		float texVecs[2][2];
		GfxColor color;
		Material* material;
		Material* materialShattered;
		PhysPreset* physPreset;
	};

	struct FxSpatialFrame
	{
		float quat[4];
		float origin[3];
	};

	struct $E43DBA5037697D705289B74D87E76C70
	{
		FxSpatialFrame frame;
		float radius;
	};

	union FxGlassPiecePlace
	{
		$E43DBA5037697D705289B74D87E76C70 __s0;
		unsigned int nextFree;
	};

	struct FxGlassPieceState
	{
		float texCoordOrigin[2];
		unsigned int supportMask;
		unsigned __int16 initIndex;
		unsigned __int16 geoDataStart;
		char defIndex;
		char pad[5];
		char vertCount;
		char holeDataCount;
		char crackDataCount;
		char fanDataCount;
		unsigned __int16 flags;
		float areaX2;
	};

	struct FxGlassPieceDynamics
	{
		int fallTime;
		int physObjId;
		int physJointId;
		float vel[3];
		float avel[3];
	};

	struct FxGlassVertex
	{
		__int16 x;
		__int16 y;
	};

	struct FxGlassHoleHeader
	{
		unsigned __int16 uniqueVertCount;
		char touchVert;
		char pad[1];
	};

	struct FxGlassCrackHeader
	{
		unsigned __int16 uniqueVertCount;
		char beginVertIndex;
		char endVertIndex;
	};

	union FxGlassGeometryData
	{
		FxGlassVertex vert;
		FxGlassHoleHeader hole;
		FxGlassCrackHeader crack;
		char asBytes[4];
		__int16 anonymous[2];
	};

	struct FxGlassInitPieceState
	{
		FxSpatialFrame frame;
		float radius;
		float texCoordOrigin[2];
		unsigned int supportMask;
		float areaX2;
		unsigned char defIndex;
		unsigned char vertCount;
		unsigned char fanDataCount;
		char pad[1];
	};

	struct FxGlassSystem
	{
		int time;
		int prevTime;
		unsigned int defCount;
		unsigned int pieceLimit;
		unsigned int pieceWordCount;
		unsigned int initPieceCount;
		unsigned int cellCount;
		unsigned int activePieceCount;
		unsigned int firstFreePiece;
		unsigned int geoDataLimit;
		unsigned int geoDataCount;
		unsigned int initGeoDataCount;
		FxGlassDef* defs;
		FxGlassPiecePlace* piecePlaces;
		FxGlassPieceState* pieceStates;
		FxGlassPieceDynamics* pieceDynamics;
		FxGlassGeometryData* geoData;
		unsigned int* isInUse;
		unsigned int* cellBits;
		char* visData;
		float(*linkOrg)[3];
		float* halfThickness;
		unsigned __int16* lightingHandles;
		FxGlassInitPieceState* initPieceStates;
		FxGlassGeometryData* initGeoData;
		bool needToCompactData;
		char initCount;
		float effectChanceAccum;
		int lastPieceDeletionTime;
	};

	struct FxWorld
	{
		const char* name;
		FxGlassSystem glassSys;
	};

	struct __declspec(align(4)) GfxSky
	{
		int skySurfCount;
		int* skyStartSurfs;
		GfxImage* skyImage;
		char skySamplerState;
	};

	struct GfxWorldDpvsPlanes
	{
		int cellCount;
		cplane_s* planes;
		unsigned __int16* nodes;
		unsigned int* sceneEntCellBits;
	};

	struct GfxCellTreeCount
	{
		int aabbTreeCount;
	};

	struct GfxAabbTree
	{
		Bounds bounds;
		unsigned __int16 childCount;
		unsigned __int16 surfaceCount;
		unsigned __int16 startSurfIndex;
		unsigned __int16 surfaceCountNoDecal;
		unsigned __int16 startSurfIndexNoDecal;
		unsigned __int16 smodelIndexCount;
		unsigned __int16* smodelIndexes;
		int childrenOffset;
	};

	struct GfxCellTree
	{
		GfxAabbTree* aabbTree;
	};

	struct GfxPortalWritable
	{
		bool isQueued;
		bool isAncestor;
		char recursionDepth;
		char hullPointCount;
		float(*hullPoints)[2];
		GfxPortal* queuedParent;
	};

	struct DpvsPlane
	{
		float coeffs[4];
	};

	struct DpvsPlanes
	{
		DpvsPlane* planes;
		int count;
	};

	struct DpvsClipPlaneSet
	{
		DpvsPlane* planes[16];
		unsigned int count;
	};

	struct DpvsStaticCellCmd
	{
		DpvsPlane* planes;
		GfxAabbTree* tree;
		char planeCount;
		char frustumPlaneCount;
		unsigned __int16 sceneViewType;
	};

	struct GfxPortal
	{
		GfxPortalWritable writable;
		DpvsPlane plane;
		float(*vertices)[3];
		unsigned __int16 cellIndex;
		char vertexCount;
		float hullAxis[2][3];
	};

	struct GfxCell
	{
		Bounds bounds;
		int portalCount;
		GfxPortal* portals;
		char reflectionProbeCount;
		char* reflectionProbes;
	};

	struct GfxReflectionProbe
	{
		float origin[3];
	};

	struct GfxLightmapArray
	{
		GfxImage* primary;
		GfxImage* secondary;
	};

	struct GfxWorldVertex
	{
		float xyz[3];
		float binormalSign;
		GfxColor color;
		float texCoord[2];
		float lmapCoord[2];
		PackedUnitVec normal;
		PackedUnitVec tangent;
	};

	struct GfxWorldVertexData
	{
		GfxWorldVertex* vertices;
		IDirect3DVertexBuffer9* worldVb;
	};

	struct GfxWorldVertexLayerData
	{
		char* data;
		IDirect3DVertexBuffer9* layerVb;
	};

	struct GfxWorldDraw
	{
		unsigned int reflectionProbeCount;
		GfxImage** reflectionProbes;
		GfxReflectionProbe* reflectionProbeOrigins;
		GfxTexture* reflectionProbeTextures;
		int lightmapCount;
		GfxLightmapArray* lightmaps;
		GfxTexture* lightmapPrimaryTextures;
		GfxTexture* lightmapSecondaryTextures;
		GfxImage* lightmapOverridePrimary;
		GfxImage* lightmapOverrideSecondary;
		unsigned int vertexCount;
		GfxWorldVertexData vd;
		unsigned int vertexLayerDataSize;
		GfxWorldVertexLayerData vld;
		unsigned int indexCount;
		unsigned __int16* indices;
	};

	struct GfxLightGridEntry
	{
		unsigned __int16 colorsIndex;
		char primaryLightIndex;
		char needsTrace;
	};

	struct GfxLightGridColors
	{
		unsigned char rgb[56][3];
	};

	struct GfxLightGrid
	{
		bool hasLightRegions;
		unsigned int lastSunPrimaryLightIndex;
		unsigned __int16 mins[3];
		unsigned __int16 maxs[3];
		unsigned int rowAxis;
		unsigned int colAxis;
		unsigned __int16* rowDataStart;
		unsigned int rawRowDataSize;
		char* rawRowData;
		unsigned int entryCount;
		GfxLightGridEntry* entries;
		unsigned int colorCount;
		GfxLightGridColors* colors;
	};

	struct GfxSModelSurfVisDataHeader
	{
		XSurface* surfs;
		unsigned __int16 smodelCount;
		unsigned __int16 smodelIndexes[1];
	};

	struct GfxBrushModelWritable
	{
		Bounds bounds;
	};

	struct __declspec(align(4)) GfxBrushModel
	{
		GfxBrushModelWritable writable;
		Bounds bounds;
		float radius;
		unsigned __int16 surfaceCount;
		unsigned __int16 startSurfIndex;
		unsigned __int16 surfaceCountNoDecal;
	};

	struct MaterialMemory
	{
		Material* material;
		int memory;
	};

	struct sunflare_t
	{
		bool hasValidData;
		Material* spriteMaterial;
		Material* flareMaterial;
		float spriteSize;
		float flareMinSize;
		float flareMinDot;
		float flareMaxSize;
		float flareMaxDot;
		float flareMaxAlpha;
		int flareFadeInTime;
		int flareFadeOutTime;
		float blindMinDot;
		float blindMaxDot;
		float blindMaxDarken;
		int blindFadeInTime;
		int blindFadeOutTime;
		float glareMinDot;
		float glareMaxDot;
		float glareMaxLighten;
		int glareFadeInTime;
		int glareFadeOutTime;
		float sunFxPosition[3];
	};

	struct XModelDrawInfo
	{
		char hasGfxEntIndex;
		char lod;
		unsigned __int16 surfId;
	};

	struct GfxSceneDynModel
	{
		XModelDrawInfo info;
		unsigned __int16 dynEntId;
	};

	struct BModelDrawInfo
	{
		unsigned __int16 surfId;
	};

	struct GfxSceneDynBrush
	{
		BModelDrawInfo info;
		unsigned __int16 dynEntId;
	};

	struct GfxShadowGeometry
	{
		unsigned __int16 surfaceCount;
		unsigned __int16 smodelCount;
		unsigned __int16* sortedSurfIndex;
		unsigned __int16* smodelIndex;
	};

	struct GfxLightRegionAxis
	{
		float dir[3];
		float midPoint;
		float halfSize;
	};

	struct GfxLightRegionHull
	{
		float kdopMidPoint[9];
		float kdopHalfSize[9];
		unsigned int axisCount;
		GfxLightRegionAxis* axis;
	};

	struct GfxLightRegion
	{
		unsigned int hullCount;
		GfxLightRegionHull* hulls;
	};

	struct GfxStaticModelInst
	{
		Bounds bounds;
		float lightingOrigin[3];
	};

	struct srfTriangles_t
	{
		unsigned int vertexLayerData;
		unsigned int firstVertex;
		unsigned __int16 vertexCount;
		unsigned __int16 triCount;
		unsigned int baseIndex;
	};

	struct GfxSurfaceLightingAndFlagsFields
	{
		unsigned char lightmapIndex;
		unsigned char reflectionProbeIndex;
		unsigned char primaryLightIndex;
		unsigned char flags;
	};

	union GfxSurfaceLightingAndFlags
	{
		GfxSurfaceLightingAndFlagsFields fields;
		unsigned int packed;
	};

	struct GfxSurface
	{
		srfTriangles_t tris;
		Material* material;
		GfxSurfaceLightingAndFlags laf;
	};

	struct GfxSurfaceBounds
	{
		Bounds bounds;
	};

	struct GfxPackedPlacement
	{
		float origin[3];
		float axis[3][3];
		float scale;
	};

	struct GfxStaticModelDrawInst
	{
		GfxPackedPlacement placement;
		XModel* model;
		unsigned __int16 cullDist;
		unsigned __int16 lightingHandle;
		unsigned char reflectionProbeIndex;
		unsigned char primaryLightIndex;
		unsigned char flags;
		unsigned char firstMtlSkinIndex;
		GfxColor groundLighting;
		unsigned __int16 cacheId[4];
	};

	struct GfxWorldDpvsStatic
	{
		unsigned int smodelCount;
		unsigned int staticSurfaceCount;
		unsigned int staticSurfaceCountNoDecal;
		unsigned int litOpaqueSurfsBegin;
		unsigned int litOpaqueSurfsEnd;
		unsigned int litTransSurfsBegin;
		unsigned int litTransSurfsEnd;
		unsigned int shadowCasterSurfsBegin;
		unsigned int shadowCasterSurfsEnd;
		unsigned int emissiveSurfsBegin;
		unsigned int emissiveSurfsEnd;
		unsigned int smodelVisDataCount;
		unsigned int surfaceVisDataCount;
		unsigned char* smodelVisData[3];
		unsigned char* surfaceVisData[3];
		unsigned __int16* sortedSurfIndex;
		GfxStaticModelInst* smodelInsts;
		GfxSurface* surfaces;
		GfxSurfaceBounds* surfacesBounds;
		GfxStaticModelDrawInst* smodelDrawInsts;
		GfxDrawSurf* surfaceMaterials;
		unsigned int* surfaceCastsSunShadow;
		volatile int usageCount;
	};

	struct GfxSModelSurfHeaderFields
	{
		char reflectionProbeIndex;
		char sceneLightIndex;
		unsigned __int16 materialSortedIndex : 12;
		unsigned __int16 visDataRefCountLessOne : 4;
	};

	union GfxSModelSurfHeader
	{
		GfxSModelSurfHeaderFields fields;
		unsigned int packed;
		unsigned __int16 array[2];
	};

	struct GfxSModelSurfVisDataRefFields
	{
		unsigned __int16 surfIndex : 4;
		unsigned __int16 visDataIndexPacked : 12;
	};

	union GfxSModelSurfVisDataRef
	{
		GfxSModelSurfVisDataRefFields fields;
		unsigned __int16 packed;
	};

	struct GfxSModelSurf
	{
		GfxSModelSurfHeader header;
		GfxSModelSurfVisDataRef visDataRefs[1];
	};

	struct GfxSModelSurfDelaySortFields
	{
		unsigned __int16 unused;
		GfxSModelSurfVisDataRef visDataRef;
		GfxSModelSurfHeader header;
	};

	union GfxSModelSurfDelaySort
	{
		GfxSModelSurfDelaySortFields fields;
		unsigned __int64 packed;
	};

	struct GfxSModelSurfBuildList
	{
		GfxSModelSurfHeader lastSurfHeader;
		GfxSModelSurf* lastSModelSurf;
		unsigned int visDataRefCount;
		char* surfDataBegin;
		char* surfDataPos;
		char* surfDataEnd;
		GfxSModelSurfHeader minDelaySortKey;
		GfxSModelSurfDelaySort* delaySurfList;
		unsigned int delaySurfCount;
		unsigned int delaySurfLimit;
	};

	struct GfxSModelSurfDrawData
	{
		unsigned int shadowCasterMaterialIndex;
		char* visData;
		unsigned int visDataUsed;
		unsigned int visDataLimit;
		GfxSModelSurfBuildList buildList[4][4];
	};

	struct GfxWorldDpvsDynamic
	{
		unsigned int dynEntClientWordCount[2];
		unsigned int dynEntClientCount[2];
		unsigned int* dynEntCellBits[2];
		char* dynEntVisData[2][3];
	};

	struct GfxHeroOnlyLight
	{
		char type;
		char unused[3];
		float color[3];
		float dir[3];
		float origin[3];
		float radius;
		float cosHalfFovOuter;
		float cosHalfFovInner;
		int exponent;
	};

	struct __declspec(align(4)) GfxWorld
	{
		const char* name;
		const char* baseName;
		int planeCount;
		int nodeCount;
		unsigned int surfaceCount;
		int skyCount;
		GfxSky* skies;
		unsigned int lastSunPrimaryLightIndex;
		unsigned int primaryLightCount;
		unsigned int sortKeyLitDecal;
		unsigned int sortKeyEffectDecal;
		unsigned int sortKeyEffectAuto;
		unsigned int sortKeyDistortion;
		GfxWorldDpvsPlanes dpvsPlanes;
		GfxCellTreeCount* aabbTreeCounts;
		GfxCellTree* aabbTrees;
		GfxCell* cells;
		GfxWorldDraw draw;
		GfxLightGrid lightGrid;
		int modelCount;
		GfxBrushModel* models;
		Bounds bounds;
		unsigned int checksum;
		int materialMemoryCount;
		MaterialMemory* materialMemory;
		sunflare_t sun;
		float outdoorLookupMatrix[4][4];
		GfxImage* outdoorImage;
		unsigned int* cellCasterBits;
		unsigned int* cellHasSunLitSurfsBits;
		GfxSceneDynModel* sceneDynModel;
		GfxSceneDynBrush* sceneDynBrush;
		unsigned int* primaryLightEntityShadowVis;
		unsigned int* primaryLightDynEntShadowVis[2];
		char* nonSunPrimaryLightForModelDynEnt;
		GfxShadowGeometry* shadowGeom;
		GfxLightRegion* lightRegion;
		GfxWorldDpvsStatic dpvs;
		GfxWorldDpvsDynamic dpvsDyn;
		unsigned int mapVtxChecksum;
		unsigned int heroOnlyLightCount;
		GfxHeroOnlyLight* heroOnlyLights;
		char fogTypesAllowed;
	};

	struct __declspec(align(4)) GfxLightImage
	{
		GfxImage* image;
		char samplerState;
	};

	struct GfxLightDef
	{
		const char* name;
		GfxLightImage attenuation;
		int lmapLookupStart;
	};

	struct Glyph
	{
		unsigned __int16 letter;
		char x0;
		char y0;
		char dx;
		char pixelWidth;
		char pixelHeight;
		float s0;
		float t0;
		float s1;
		float t1;
	};

	struct Font_s
	{
		const char* fontName;
		int pixelHeight;
		int glyphCount;
		Material* material;
		Material* glowMaterial;
		Glyph* glyphs;
	};

	struct rectDef_s
	{
		float x;
		float y;
		float w;
		float h;
		char horzAlign;
		char vertAlign;
	};

	static_assert(sizeof(rectDef_s) == 0x14);

	struct windowDef_t
	{
		const char* name;
		rectDef_s rect;
		rectDef_s rectClient;
		const char* group;
		int style;
		int border;
		int ownerDraw;
		int ownerDrawFlags;
		float borderSize;
		int staticFlags;
		int dynamicFlags[1];
		int nextTime;
		float foreColor[4];
		float backColor[4];
		float borderColor[4];
		float outlineColor[4];
		float disableColor[4];
		Material* background;
	};

	static_assert(sizeof(windowDef_t) == 0xA4);

	enum expDataType
	{
		VAL_INT = 0x0,
		VAL_FLOAT = 0x1,
		VAL_STRING = 0x2,
		NUM_INTERNAL_DATATYPES = 0x3,
		VAL_FUNCTION = 0x3,
		NUM_DATATYPES = 0x4,
	};

	struct ExpressionString
	{
		const char* string;
	};

	union operandInternalDataUnion
	{
		int intVal;
		float floatVal;
		ExpressionString stringVal;
		Statement_s* function;
	};

	struct Operand
	{
		expDataType dataType;
		operandInternalDataUnion internals;
	};

	enum operationEnum
	{
		OP_NOOP = 0x0,
		OP_RIGHTPAREN = 0x1,
		OP_MULTIPLY = 0x2,
		OP_DIVIDE = 0x3,
		OP_MODULUS = 0x4,
		OP_ADD = 0x5,
		OP_SUBTRACT = 0x6,
		OP_NOT = 0x7,
		OP_LESSTHAN = 0x8,
		OP_LESSTHANEQUALTO = 0x9,
		OP_GREATERTHAN = 0xA,
		OP_GREATERTHANEQUALTO = 0xB,
		OP_EQUALS = 0xC,
		OP_NOTEQUAL = 0xD,
		OP_AND = 0xE,
		OP_OR = 0xF,
		OP_LEFTPAREN = 0x10,
		OP_COMMA = 0x11,
		OP_BITWISEAND = 0x12,
		OP_BITWISEOR = 0x13,
		OP_BITWISENOT = 0x14,
		OP_BITSHIFTLEFT = 0x15,
		OP_BITSHIFTRIGHT = 0x16,
		OP_STATICDVARINT = 0x17,
		OP_FIRSTFUNCTIONCALL = 0x17,
		OP_STATICDVARBOOL = 0x18,
		OP_STATICDVARFLOAT = 0x19,
		OP_STATICDVARSTRING = 0x1A,
		OP_TOINT = 0x1B,
		OP_TOSTRING = 0x1C,
		OP_TOFLOAT = 0x1D,
		LAST_COMMONLY_CALLED_FUNCTION = 0x1D,
		OP_SIN = 0x1E,
		OP_COS = 0x1F,
		OP_MIN = 0x20,
		OP_MAX = 0x21,
		OP_MILLISECONDS = 0x22,
		OP_DVARINT = 0x23,
		OP_DVARBOOL = 0x24,
		OP_DVARFLOAT = 0x25,
		OP_DVARSTRING = 0x26,
		OP_STAT = 0x27,
		OP_UIACTIVE = 0x28,
		OP_FLASHBANGED = 0x29,
		OP_USINGVEHICLE = 0x2A,
		OP_MISSILECAM = 0x2B,
		OP_SCOPED = 0x2C,
		OP_SCOPEDTHERMAL = 0x2D,
		OP_SCOREBOARDVISIBLE = 0x2E,
		OP_INKILLCAM = 0x2F,
		OP_INKILLCAM_NPC = 0x30,
		OP_PLAYERFIELD = 0x31,
		OP_GET_PLAYER_PERK = 0x32,
		OP_SELECTINGLOCATION = 0x33,
		OP_SELECTINGDIRECTION = 0x34,
		OP_TEAMFIELD = 0x35,
		OP_OTHERTEAMFIELD = 0x36,
		OP_MARINESFIELD = 0x37,
		OP_OPFORFIELD = 0x38,
		OP_MENUISOPEN = 0x39,
		OP_WRITINGDATA = 0x3A,
		OP_INLOBBY = 0x3B,
		OP_INPRIVATEPARTY = 0x3C,
		OP_PRIVATEPARTYHOST = 0x3D,
		OP_PRIVATEPARTYHOSTINLOBBY = 0x3E,
		OP_ALONEINPARTY = 0x3F,
		OP_ADSJAVELIN = 0x40,
		OP_WEAPLOCKBLINK = 0x41,
		OP_WEAPATTACKTOP = 0x42,
		OP_WEAPATTACKDIRECT = 0x43,
		OP_WEAPLOCKING = 0x44,
		OP_WEAPLOCKED = 0x45,
		OP_WEAPLOCKTOOCLOSE = 0x46,
		OP_WEAPLOCKSCREENPOSX = 0x47,
		OP_WEAPLOCKSCREENPOSY = 0x48,
		OP_SECONDSASTIME = 0x49,
		OP_TABLELOOKUP = 0x4A,
		OP_TABLELOOKUPBYROW = 0x4B,
		OP_TABLEGETROWNUM = 0x4C,
		OP_LOCALIZESTRING = 0x4D,
		OP_LOCALVARINT = 0x4E,
		OP_LOCALVARBOOL = 0x4F,
		OP_LOCALVARFLOAT = 0x50,
		OP_LOCALVARSTRING = 0x51,
		OP_TIMELEFT = 0x52,
		OP_SECONDSASCOUNTDOWN = 0x53,
		OP_GAMEMSGWNDACTIVE = 0x54,
		OP_GAMETYPENAME = 0x55,
		OP_GAMETYPE = 0x56,
		OP_GAMETYPEDESCRIPTION = 0x57,
		OP_SCORE = 0x58,
		OP_FRIENDSONLINE = 0x59,
		OP_FOLLOWING = 0x5A,
		OP_SPECTATINGFREE = 0x5B,
		OP_STATRANGEBITSSET = 0x5C,
		OP_KEYBINDING = 0x5D,
		OP_ACTIONSLOTUSABLE = 0x5E,
		OP_HUDFADE = 0x5F,
		OP_MAXPLAYERS = 0x60,
		OP_ACCEPTINGINVITE = 0x61,
		OP_ISINTERMISSION = 0x62,
		OP_GAMEHOST = 0x63,
		OP_PARTYHASMISSINGMAPPACK = 0x64,
		OP_PARTYMISSINGMAPPACKERROR = 0x65,
		OP_ANYNEWMAPPACKS = 0x66,
		OP_AMISELECTED = 0x67,
		OP_PARTYSTATUSSTRING = 0x68,
		OP_ATTACHED_CONTROLLER_COUNT = 0x69,
		OP_IS_SPLIT_SCREEN_ONLINE_POSSIBLE = 0x6A,
		OP_SPLITSCREENPLAYERCOUNT = 0x6B,
		OP_GETPLAYERDATA = 0x6C,
		OP_GETPLAYERDATASPLITSCREEN = 0x6D,
		OP_EXPERIENCE_FOR_LEVEL = 0x6E,
		OP_LEVEL_FOR_EXPERIENCE = 0x6F,
		OP_IS_ITEM_UNLOCKED = 0x70,
		OP_IS_ITEM_UNLOCKEDSPLITSCREEN = 0x71,
		OP_DEBUG_PRINT = 0x72,
		OP_GETPLAYERDATA_ANYBOOLTRUE = 0x73,
		OP_WEAPON_CLASS_NEW = 0x74,
		OP_WEAPONNAME = 0x75,
		OP_ISRELOADING = 0x76,
		OP_SAVE_GAME_AVAILABLE = 0x77,
		OP_UNLOCKED_ITEM_COUNT = 0x78,
		OP_UNLOCKED_ITEM_COUNT_SPLITSCREEN = 0x79,
		OP_UNLOCKED_ITEM = 0x7A,
		OP_UNLOCKED_ITEM_SPLITSCREEN = 0x7B,
		OP_MAIL_SUBJECT = 0x7C,
		OP_MAIL_FROM = 0x7D,
		OP_MAIL_RECEIVED = 0x7E,
		OP_MAIL_BODY = 0x7F,
		OP_MAIL_LOOT_LOCALIZED = 0x80,
		OP_MAIL_GIVES_LOOT = 0x81,
		OP_ANY_NEW_MAIL = 0x82,
		OP_MAIL_TIME_TO_FOLLOWUP = 0x83,
		OP_MAIL_LOOT_TYPE = 0x84,
		OP_MAIL_RAN_LOTTERY = 0x85,
		OP_LOTTERY_LOOT_LOCALIZED = 0x86,
		OP_RADAR_IS_JAMMED = 0x87,
		OP_RADAR_JAM_INTENSITY = 0x88,
		OP_RADAR_IS_ENABLED = 0x89,
		OP_EMP_JAMMED = 0x8A,
		OP_PLAYERADS = 0x8B,
		OP_WEAPON_HEAT_ACTIVE = 0x8C,
		OP_WEAPON_HEAT_VALUE = 0x8D,
		OP_WEAPON_HEAT_OVERHEATED = 0x8E,
		OP_SPLASH_TEXT = 0x8F,
		OP_SPLASH_DESCRIPTION = 0x90,
		OP_SPLASH_MATERIAL = 0x91,
		OP_SPLASH_HAS_ICON = 0x92,
		OP_SPLASH_ROWNUM = 0x93,
		OP_GETFOCUSED_NAME = 0x94,
		OP_GETFOCUSED_X = 0x95,
		OP_GETFOCUSED_Y = 0x96,
		OP_GETFOCUSED_W = 0x97,
		OP_GETFOCUSED_H = 0x98,
		OP_GETITEMDEF_X = 0x99,
		OP_GETITEMDEF_Y = 0x9A,
		OP_GETITEMDEF_W = 0x9B,
		OP_GETITEMDEF_H = 0x9C,
		OP_PLAYLISTFIELD = 0x9D,
		OP_SCOREBOARD_EXTERNALMUTE_NOTICE = 0x9E,
		OP_CLIENT_MATCH_DATA = 0x9F,
		OP_CLIENT_MATCH_DATA_DEF = 0xA0,
		OP_GET_MAP_NAME = 0xA1,
		OP_GET_MAP_IMAGE = 0xA2,
		OP_GET_MAP_CUSTOM = 0xA3,
		OP_GET_MIGRATION_STATUS = 0xA4,
		OP_GET_PLAYERCARD_INFO = 0xA5,
		OP_IS_OFFLINE_PROFILE_SELECTED = 0xA6,
		OP_COOP_PLAYERFIELD = 0xA7,
		OP_IS_COOP = 0xA8,
		OP_GETPARTYSTATUS = 0xA9,
		OP_GETSEARCHPARAMS = 0xAA,
		OP_GETTIMEPLAYED = 0xAB,
		OP_IS_SELECTED_PLAYER_FRIEND = 0xAC,
		OP_GETCHARBYINDEX = 0xAD,
		OP_GETPLAYERPROFILEDATA = 0xAE,
		OP_IS_PROFILE_SIGNED_IN = 0xAF,
		OP_GET_WAIT_POPUP_STATUS = 0xB0,
		NUM_OPERATORS = 0xB1,
	};

	union entryInternalData
	{
		operationEnum op;
		Operand operand;
	};

	struct expressionEntry
	{
		int type;
		entryInternalData data;
	};

	struct UIFunctionList
	{
		int totalFunctions;
		Statement_s** functions;
	};

	union DvarValue
	{
		bool enabled;
		int integer;
		unsigned int unsignedInt;
		float value;
		float vector[4];
		const char* string;
		unsigned char color[4];
	};

	static_assert(sizeof(DvarValue) == 0x10);

	struct enum_limit
	{
		int stringCount;
		const char** strings;
	};

	struct int_limit
	{
		int min;
		int max;
	};

	struct float_limit
	{
		float min;
		float max;
	};

	union DvarLimits
	{
		enum_limit enumeration;
		int_limit integer;
		float_limit value;
		float_limit vector;
	};

	static_assert(sizeof(DvarLimits) == 0x8);

	struct dvar_t
	{
		const char* name;
		const char* description;
		unsigned int flags;
		dvar_type type;
		bool modified;
		DvarValue current;
		DvarValue latched;
		DvarValue reset;
		DvarLimits domain;
		bool(__cdecl* domainFunc)(dvar_t*, DvarValue);
		dvar_t* hashNext;
	};

	static_assert(sizeof(dvar_t) == 0x50);

	struct StaticDvar
	{
		dvar_t* dvar;
		char* dvarName;
	};

	struct StaticDvarList
	{
		int numStaticDvars;
		StaticDvar** staticDvars;
	};

	struct StringList
	{
		int totalStrings;
		const char** strings;
	};

	struct ExpressionSupportingData
	{
		UIFunctionList uifunctions;
		StaticDvarList staticDvarList;
		StringList uiStrings;
	};

	struct Statement_s
	{
		int numEntries;
		expressionEntry* entries;
		ExpressionSupportingData* supportingData;
		int lastExecuteTime;
		Operand lastResult;
	};

	enum EventType
	{
		EVENT_UNCONDITIONAL = 0x0,
		EVENT_IF = 0x1,
		EVENT_ELSE = 0x2,
		EVENT_SET_LOCAL_VAR_BOOL = 0x3,
		EVENT_SET_LOCAL_VAR_INT = 0x4,
		EVENT_SET_LOCAL_VAR_FLOAT = 0x5,
		EVENT_SET_LOCAL_VAR_STRING = 0x6,
		EVENT_COUNT = 0x7,
	};

	struct ConditionalScript
	{
		MenuEventHandlerSet* eventHandlerSet;
		Statement_s* eventExpression;
	};

	struct SetLocalVarData
	{
		const char* localVarName;
		Statement_s* expression;
	};

	union EventData
	{
		const char* unconditionalScript;
		ConditionalScript* conditionalScript;
		struct MenuEventHandlerSet* elseScript;
		SetLocalVarData* setLocalVarData;
	};

	struct __declspec(align(4)) MenuEventHandler
	{
		EventData eventData;
		char eventType;
	};

	struct MenuEventHandlerSet
	{
		int eventHandlerCount;
		MenuEventHandler** eventHandlers;
	};

	struct ItemKeyHandler
	{
		int key;
		MenuEventHandlerSet* action;
		ItemKeyHandler* next;
	};

	struct columnInfo_s
	{
		int pos;
		int width;
		int maxChars;
		int alignment;
	};

	struct listBoxDef_s
	{
		int mousePos;
		int startPos[1];
		int endPos[1];
		int drawPadding;
		float elementWidth;
		float elementHeight;
		int elementStyle;
		int numColumns;
		columnInfo_s columnInfo[16];
		MenuEventHandlerSet* onDoubleClick;
		int notselectable;
		int noScrollBars;
		int usePaging;
		float selectBorder[4];
		Material* selectIcon;
	};

	struct editFieldDef_s
	{
		float minVal;
		float maxVal;
		float defVal;
		float range;
		int maxChars;
		int maxCharsGotoNext;
		int maxPaintChars;
		int paintOffset;
	};

	struct multiDef_s
	{
		const char* dvarList[32];
		const char* dvarStr[32];
		float dvarValue[32];
		int count;
		int strDef;
	};

	struct newsTickerDef_s
	{
		int feedId;
		int speed;
		int spacing;
		int lastTime;
		int start;
		int end;
		float x;
	};

	struct textScrollDef_s
	{
		int startTime;
	};

	union itemDefData_t
	{
		listBoxDef_s* listBox;
		editFieldDef_s* editField;
		multiDef_s* multi;
		const char* enumDvarName;
		newsTickerDef_s* ticker;
		textScrollDef_s* scroll;
		void* data;
	};

	struct ItemFloatExpression
	{
		int target;
		Statement_s* expression;
	};

	enum ItemDefType
	{
		ITEM_TYPE_TEXT = 0x0,
		ITEM_TYPE_BUTTON = 0x1,
		ITEM_TYPE_RADIOBUTTON = 0x2,
		ITEM_TYPE_CHECKBOX = 0x3,
		ITEM_TYPE_EDITFIELD = 0x4,
		ITEM_TYPE_COMBO = 0x5,
		ITEM_TYPE_LISTBOX = 0x6,
		ITEM_TYPE_MODEL = 0x7,
		ITEM_TYPE_OWNERDRAW = 0x8,
		ITEM_TYPE_NUMERICFIELD = 0x9,
		ITEM_TYPE_SLIDER = 0xA,
		ITEM_TYPE_YESNO = 0xB,
		ITEM_TYPE_MULTI = 0xC,
		ITEM_TYPE_DVARENUM = 0xD,
		ITEM_TYPE_BIND = 0xE,
		ITEM_TYPE_MENUMODEL = 0xF,
		ITEM_TYPE_VALIDFILEFIELD = 0x10,
		ITEM_TYPE_DECIMALFIELD = 0x11,
		ITEM_TYPE_UPREDITFIELD = 0x12,
		ITEM_TYPE_GAME_MESSAGE_WINDOW = 0x13,
		ITEM_TYPE_NEWS_TICKER = 0x14,
		ITEM_TYPE_TEXT_SCROLL = 0x15,
		ITEM_TYPE_EMAILFIELD = 0x16,
		ITEM_TYPE_PASSWORDFIELD = 0x17,
	};

	struct itemDef_s
	{
		windowDef_t window;
		rectDef_s textRect[1];
		int type;
		int dataType;
		int alignment;
		int fontEnum;
		int textAlignMode;
		float textalignx;
		float textaligny;
		float textscale;
		int textStyle;
		int gameMsgWindowIndex;
		int gameMsgWindowMode;
		const char* text;
		int itemFlags;
		menuDef_t* parent;
		MenuEventHandlerSet* mouseEnterText;
		MenuEventHandlerSet* mouseExitText;
		MenuEventHandlerSet* mouseEnter;
		MenuEventHandlerSet* mouseExit;
		MenuEventHandlerSet* action;
		MenuEventHandlerSet* accept;
		MenuEventHandlerSet* onFocus;
		MenuEventHandlerSet* leaveFocus;
		const char* dvar;
		const char* dvarTest;
		ItemKeyHandler* onKey;
		const char* enableDvar;
		const char* localVar;
		int dvarFlags;
		snd_alias_list_t* focusSound;
		float special;
		int cursorPos[1];
		itemDefData_t typeData;
		int imageTrack;
		int floatExpressionCount;
		ItemFloatExpression* floatExpressions;
		Statement_s* visibleExp;
		Statement_s* disabledExp;
		Statement_s* textExp;
		Statement_s* materialExp;
		float glowColor[4];
		bool decayActive;
		int fxBirthTime;
		int fxLetterTime;
		int fxDecayStartTime;
		int fxDecayDuration;
		int lastSoundPlayedTime;
	};

	struct menuTransition
	{
		int transitionType;
		int targetField;
		int startTime;
		float startVal;
		float endVal;
		float time;
		int endTriggerType;
	};

	struct menuDef_t
	{
		windowDef_t window;
		const char* font;
		int fullScreen;
		int itemCount;
		int fontIndex;
		int cursorItem[1];
		int fadeCycle;
		float fadeClamp;
		float fadeAmount;
		float fadeInAmount;
		float blurRadius;
		MenuEventHandlerSet* onOpen;
		MenuEventHandlerSet* onCloseRequest;
		MenuEventHandlerSet* onClose;
		MenuEventHandlerSet* onESC;
		ItemKeyHandler* onKey;
		Statement_s* visibleExp;
		const char* allowedBinding;
		const char* soundName;
		int imageTrack;
		float focusColor[4];
		Statement_s* rectXExp;
		Statement_s* rectYExp;
		Statement_s* rectWExp;
		Statement_s* rectHExp;
		Statement_s* openSoundExp;
		Statement_s* closeSoundExp;
		itemDef_s** items;
		menuTransition scaleTransition[1];
		menuTransition alphaTransition[1];
		menuTransition xTransition[1];
		menuTransition yTransition[1];
		ExpressionSupportingData* expressionData;
	};

	struct MenuList
	{
		const char* name;
		int menuCount;
		menuDef_t** menus;
	};

	struct LocalizeEntry
	{
		const char* value;
		const char* name;
	};

	enum weapType_t
	{
		WEAPTYPE_BULLET = 0x0,
		WEAPTYPE_GRENADE = 0x1,
		WEAPTYPE_PROJECTILE = 0x2,
		WEAPTYPE_RIOTSHIELD = 0x3,
		WEAPTYPE_NUM = 0x4,
	};

	enum weapClass_t
	{
		WEAPCLASS_RIFLE = 0x0,
		WEAPCLASS_SNIPER = 0x1,
		WEAPCLASS_MG = 0x2,
		WEAPCLASS_SMG = 0x3,
		WEAPCLASS_SPREAD = 0x4,
		WEAPCLASS_PISTOL = 0x5,
		WEAPCLASS_GRENADE = 0x6,
		WEAPCLASS_ROCKETLAUNCHER = 0x7,
		WEAPCLASS_TURRET = 0x8,
		WEAPCLASS_THROWINGKNIFE = 0x9,
		WEAPCLASS_NON_PLAYER = 0xA,
		WEAPCLASS_ITEM = 0xB,
		WEAPCLASS_NUM = 0xC,
	};

	enum PenetrateType
	{
		PENETRATE_TYPE_NONE = 0x0,
		PENETRATE_TYPE_SMALL = 0x1,
		PENETRATE_TYPE_MEDIUM = 0x2,
		PENETRATE_TYPE_LARGE = 0x3,
		PENETRATE_TYPE_COUNT = 0x4,
	};

	enum weapInventoryType_t
	{
		WEAPINVENTORY_PRIMARY = 0x0,
		WEAPINVENTORY_OFFHAND = 0x1,
		WEAPINVENTORY_ITEM = 0x2,
		WEAPINVENTORY_ALTMODE = 0x3,
		WEAPINVENTORY_EXCLUSIVE = 0x4,
		WEAPINVENTORY_SCAVENGER = 0x5,
		WEAPINVENTORYCOUNT = 0x6,
	};

	enum weapFireType_t
	{
		WEAPON_FIRETYPE_FULLAUTO = 0x0,
		WEAPON_FIRETYPE_SINGLESHOT = 0x1,
		WEAPON_FIRETYPE_BURSTFIRE2 = 0x2,
		WEAPON_FIRETYPE_BURSTFIRE3 = 0x3,
		WEAPON_FIRETYPE_BURSTFIRE4 = 0x4,
		WEAPON_FIRETYPE_DOUBLEBARREL = 0x5,
		WEAPON_FIRETYPECOUNT = 0x6,
		WEAPON_FIRETYPE_BURSTFIRE_FIRST = 0x2,
		WEAPON_FIRETYPE_BURSTFIRE_LAST = 0x4,
	};
	enum weapStance_t
	{
		WEAPSTANCE_STAND = 0x0,
		WEAPSTANCE_DUCK = 0x1,
		WEAPSTANCE_PRONE = 0x2,
		WEAPSTANCE_NUM = 0x3,
	};

	enum activeReticleType_t
	{
		VEH_ACTIVE_RETICLE_NONE = 0x0,
		VEH_ACTIVE_RETICLE_PIP_ON_A_STICK = 0x1,
		VEH_ACTIVE_RETICLE_BOUNCING_DIAMOND = 0x2,
		VEH_ACTIVE_RETICLE_COUNT = 0x3,
	};

	enum weaponIconRatioType_t
	{
		WEAPON_ICON_RATIO_1TO1 = 0x0,
		WEAPON_ICON_RATIO_2TO1 = 0x1,
		WEAPON_ICON_RATIO_4TO1 = 0x2,
		WEAPON_ICON_RATIO_COUNT = 0x3,
	};

	enum ammoCounterClipType_t
	{
		AMMO_COUNTER_CLIP_NONE = 0x0,
		AMMO_COUNTER_CLIP_MAGAZINE = 0x1,
		AMMO_COUNTER_CLIP_SHORTMAGAZINE = 0x2,
		AMMO_COUNTER_CLIP_SHOTGUN = 0x3,
		AMMO_COUNTER_CLIP_ROCKET = 0x4,
		AMMO_COUNTER_CLIP_BELTFED = 0x5,
		AMMO_COUNTER_CLIP_ALTWEAPON = 0x6,
		AMMO_COUNTER_CLIP_COUNT = 0x7,
	};

	enum weapOverlayReticle_t
	{
		WEAPOVERLAYRETICLE_NONE = 0x0,
		WEAPOVERLAYRETICLE_CROSSHAIR = 0x1,
		WEAPOVERLAYRETICLE_NUM = 0x2,
	};

	enum WeapOverlayInteface_t
	{
		WEAPOVERLAYINTERFACE_NONE = 0x0,
		WEAPOVERLAYINTERFACE_JAVELIN = 0x1,
		WEAPOVERLAYINTERFACE_TURRETSCOPE = 0x2,
		WEAPOVERLAYINTERFACECOUNT = 0x3,
	};

	enum weapProjExposion_t
	{
		WEAPPROJEXP_GRENADE = 0x0,
		WEAPPROJEXP_ROCKET = 0x1,
		WEAPPROJEXP_FLASHBANG = 0x2,
		WEAPPROJEXP_NONE = 0x3,
		WEAPPROJEXP_DUD = 0x4,
		WEAPPROJEXP_SMOKE = 0x5,
		WEAPPROJEXP_HEAVY = 0x6,
		WEAPPROJEXP_NUM = 0x7,
	};

	enum WeapStickinessType
	{
		WEAPSTICKINESS_NONE = 0x0,
		WEAPSTICKINESS_ALL = 0x1,
		WEAPSTICKINESS_ALL_ORIENT = 0x2,
		WEAPSTICKINESS_GROUND = 0x3,
		WEAPSTICKINESS_GROUND_WITH_YAW = 0x4,
		WEAPSTICKINESS_KNIFE = 0x5,
		WEAPSTICKINESS_COUNT = 0x6,
	};

	enum guidedMissileType_t
	{
		MISSILE_GUIDANCE_NONE = 0x0,
		MISSILE_GUIDANCE_SIDEWINDER = 0x1,
		MISSILE_GUIDANCE_HELLFIRE = 0x2,
		MISSILE_GUIDANCE_JAVELIN = 0x3,
		MISSILE_GUIDANCE_COUNT = 0x4,
	};

	struct TracerDef
	{
		const char* name;
		Material* material;
		unsigned int drawInterval;
		float speed;
		float beamLength;
		float beamWidth;
		float screwRadius;
		float screwDist;
		float colors[5][4];
	};

	struct NetField
	{
		char* name;
		int offset;
		int bits;
		char changeHints;
	};

	struct __declspec(align(4)) WeaponDef
	{
		const char* szOverlayName;
		XModel** gunXModel;
		XModel* handXModel;
		const char** szXAnimsRightHanded;
		const char** szXAnimsLeftHanded;
		const char* szModeName;
		unsigned __int16* notetrackSoundMapKeys;
		unsigned __int16* notetrackSoundMapValues;
		unsigned __int16* notetrackRumbleMapKeys;
		unsigned __int16* notetrackRumbleMapValues;
		int playerAnimType;
		weapType_t weapType;
		weapClass_t weapClass;
		PenetrateType penetrateType;
		weapInventoryType_t inventoryType;
		weapFireType_t fireType;
		OffhandClass offhandClass;
		weapStance_t stance;
		FxEffectDef* viewFlashEffect;
		FxEffectDef* worldFlashEffect;
		snd_alias_list_t* pickupSound;
		snd_alias_list_t* pickupSoundPlayer;
		snd_alias_list_t* ammoPickupSound;
		snd_alias_list_t* ammoPickupSoundPlayer;
		snd_alias_list_t* projectileSound;
		snd_alias_list_t* pullbackSound;
		snd_alias_list_t* pullbackSoundPlayer;
		snd_alias_list_t* fireSound;
		snd_alias_list_t* fireSoundPlayer;
		snd_alias_list_t* fireSoundPlayerAkimbo;
		snd_alias_list_t* fireLoopSound;
		snd_alias_list_t* fireLoopSoundPlayer;
		snd_alias_list_t* fireStopSound;
		snd_alias_list_t* fireStopSoundPlayer;
		snd_alias_list_t* fireLastSound;
		snd_alias_list_t* fireLastSoundPlayer;
		snd_alias_list_t* emptyFireSound;
		snd_alias_list_t* emptyFireSoundPlayer;
		snd_alias_list_t* meleeSwipeSound;
		snd_alias_list_t* meleeSwipeSoundPlayer;
		snd_alias_list_t* meleeHitSound;
		snd_alias_list_t* meleeMissSound;
		snd_alias_list_t* rechamberSound;
		snd_alias_list_t* rechamberSoundPlayer;
		snd_alias_list_t* reloadSound;
		snd_alias_list_t* reloadSoundPlayer;
		snd_alias_list_t* reloadEmptySound;
		snd_alias_list_t* reloadEmptySoundPlayer;
		snd_alias_list_t* reloadStartSound;
		snd_alias_list_t* reloadStartSoundPlayer;
		snd_alias_list_t* reloadEndSound;
		snd_alias_list_t* reloadEndSoundPlayer;
		snd_alias_list_t* detonateSound;
		snd_alias_list_t* detonateSoundPlayer;
		snd_alias_list_t* nightVisionWearSound;
		snd_alias_list_t* nightVisionWearSoundPlayer;
		snd_alias_list_t* nightVisionRemoveSound;
		snd_alias_list_t* nightVisionRemoveSoundPlayer;
		snd_alias_list_t* altSwitchSound;
		snd_alias_list_t* altSwitchSoundPlayer;
		snd_alias_list_t* raiseSound;
		snd_alias_list_t* raiseSoundPlayer;
		snd_alias_list_t* firstRaiseSound;
		snd_alias_list_t* firstRaiseSoundPlayer;
		snd_alias_list_t* putawaySound;
		snd_alias_list_t* putawaySoundPlayer;
		snd_alias_list_t* scanSound;
		snd_alias_list_t** bounceSound;
		FxEffectDef* viewShellEjectEffect;
		FxEffectDef* worldShellEjectEffect;
		FxEffectDef* viewLastShotEjectEffect;
		FxEffectDef* worldLastShotEjectEffect;
		Material* reticleCenter;
		Material* reticleSide;
		int iReticleCenterSize;
		int iReticleSideSize;
		int iReticleMinOfs;
		activeReticleType_t activeReticleType;
		float vStandMove[3];
		float vStandRot[3];
		float strafeMove[3];
		float strafeRot[3];
		float vDuckedOfs[3];
		float vDuckedMove[3];
		float vDuckedRot[3];
		float vProneOfs[3];
		float vProneMove[3];
		float vProneRot[3];
		float fPosMoveRate;
		float fPosProneMoveRate;
		float fStandMoveMinSpeed;
		float fDuckedMoveMinSpeed;
		float fProneMoveMinSpeed;
		float fPosRotRate;
		float fPosProneRotRate;
		float fStandRotMinSpeed;
		float fDuckedRotMinSpeed;
		float fProneRotMinSpeed;
		XModel** worldModel;
		XModel* worldClipModel;
		XModel* rocketModel;
		XModel* knifeModel;
		XModel* worldKnifeModel;
		Material* hudIcon;
		weaponIconRatioType_t hudIconRatio;
		Material* pickupIcon;
		weaponIconRatioType_t pickupIconRatio;
		Material* ammoCounterIcon;
		weaponIconRatioType_t ammoCounterIconRatio;
		ammoCounterClipType_t ammoCounterClip;
		int iStartAmmo;
		const char* szAmmoName;
		int iAmmoIndex;
		const char* szClipName;
		int iClipIndex;
		int iMaxAmmo;
		int shotCount;
		const char* szSharedAmmoCapName;
		int iSharedAmmoCapIndex;
		int iSharedAmmoCap;
		int damage;
		int playerDamage;
		int iMeleeDamage;
		int iDamageType;
		int iFireDelay;
		int iMeleeDelay;
		int meleeChargeDelay;
		int iDetonateDelay;
		int iRechamberTime;
		int rechamberTimeOneHanded;
		int iRechamberBoltTime;
		int iHoldFireTime;
		int iDetonateTime;
		int iMeleeTime;
		int meleeChargeTime;
		int iReloadTime;
		int reloadShowRocketTime;
		int iReloadEmptyTime;
		int iReloadAddTime;
		int iReloadStartTime;
		int iReloadStartAddTime;
		int iReloadEndTime;
		int iDropTime;
		int iRaiseTime;
		int iAltDropTime;
		int quickDropTime;
		int quickRaiseTime;
		int iBreachRaiseTime;
		int iEmptyRaiseTime;
		int iEmptyDropTime;
		int sprintInTime;
		int sprintLoopTime;
		int sprintOutTime;
		int stunnedTimeBegin;
		int stunnedTimeLoop;
		int stunnedTimeEnd;
		int nightVisionWearTime;
		int nightVisionWearTimeFadeOutEnd;
		int nightVisionWearTimePowerUp;
		int nightVisionRemoveTime;
		int nightVisionRemoveTimePowerDown;
		int nightVisionRemoveTimeFadeInStart;
		int fuseTime;
		int aiFuseTime;
		float autoAimRange;
		float aimAssistRange;
		float aimAssistRangeAds;
		float aimPadding;
		float enemyCrosshairRange;
		float moveSpeedScale;
		float adsMoveSpeedScale;
		float sprintDurationScale;
		float fAdsZoomInFrac;
		float fAdsZoomOutFrac;
		Material* overlayMaterial;
		Material* overlayMaterialLowRes;
		Material* overlayMaterialEMP;
		Material* overlayMaterialEMPLowRes;
		weapOverlayReticle_t overlayReticle;
		WeapOverlayInteface_t overlayInterface;
		float overlayWidth;
		float overlayHeight;
		float overlayWidthSplitscreen;
		float overlayHeightSplitscreen;
		float fAdsBobFactor;
		float fAdsViewBobMult;
		float fHipSpreadStandMin;
		float fHipSpreadDuckedMin;
		float fHipSpreadProneMin;
		float hipSpreadStandMax;
		float hipSpreadDuckedMax;
		float hipSpreadProneMax;
		float fHipSpreadDecayRate;
		float fHipSpreadFireAdd;
		float fHipSpreadTurnAdd;
		float fHipSpreadMoveAdd;
		float fHipSpreadDuckedDecay;
		float fHipSpreadProneDecay;
		float fHipReticleSidePos;
		float fAdsIdleAmount;
		float fHipIdleAmount;
		float adsIdleSpeed;
		float hipIdleSpeed;
		float fIdleCrouchFactor;
		float fIdleProneFactor;
		float fGunMaxPitch;
		float fGunMaxYaw;
		float swayMaxAngle;
		float swayLerpSpeed;
		float swayPitchScale;
		float swayYawScale;
		float swayHorizScale;
		float swayVertScale;
		float swayShellShockScale;
		float adsSwayMaxAngle;
		float adsSwayLerpSpeed;
		float adsSwayPitchScale;
		float adsSwayYawScale;
		float adsSwayHorizScale;
		float adsSwayVertScale;
		float adsViewErrorMin;
		float adsViewErrorMax;
		PhysCollmap* physCollmap;
		float dualWieldViewModelOffset;
		weaponIconRatioType_t killIconRatio;
		int iReloadAmmoAdd;
		int iReloadStartAdd;
		int ammoDropStockMin;
		int ammoDropClipPercentMin;
		int ammoDropClipPercentMax;
		int iExplosionRadius;
		int iExplosionRadiusMin;
		int iExplosionInnerDamage;
		int iExplosionOuterDamage;
		float damageConeAngle;
		float bulletExplDmgMult;
		float bulletExplRadiusMult;
		int iProjectileSpeed;
		int iProjectileSpeedUp;
		int iProjectileSpeedForward;
		int iProjectileActivateDist;
		float projLifetime;
		float timeToAccelerate;
		float projectileCurvature;
		XModel* projectileModel;
		weapProjExposion_t projExplosion;
		FxEffectDef* projExplosionEffect;
		FxEffectDef* projDudEffect;
		snd_alias_list_t* projExplosionSound;
		snd_alias_list_t* projDudSound;
		WeapStickinessType stickiness;
		float lowAmmoWarningThreshold;
		float ricochetChance;
		float* parallelBounce;
		float* perpendicularBounce;
		FxEffectDef* projTrailEffect;
		FxEffectDef* projBeaconEffect;
		float vProjectileColor[3];
		guidedMissileType_t guidedMissileType;
		float maxSteeringAccel;
		int projIgnitionDelay;
		FxEffectDef* projIgnitionEffect;
		snd_alias_list_t* projIgnitionSound;
		float fAdsAimPitch;
		float fAdsCrosshairInFrac;
		float fAdsCrosshairOutFrac;
		int adsGunKickReducedKickBullets;
		float adsGunKickReducedKickPercent;
		float fAdsGunKickPitchMin;
		float fAdsGunKickPitchMax;
		float fAdsGunKickYawMin;
		float fAdsGunKickYawMax;
		float fAdsGunKickAccel;
		float fAdsGunKickSpeedMax;
		float fAdsGunKickSpeedDecay;
		float fAdsGunKickStaticDecay;
		float fAdsViewKickPitchMin;
		float fAdsViewKickPitchMax;
		float fAdsViewKickYawMin;
		float fAdsViewKickYawMax;
		float fAdsViewScatterMin;
		float fAdsViewScatterMax;
		float fAdsSpread;
		int hipGunKickReducedKickBullets;
		float hipGunKickReducedKickPercent;
		float fHipGunKickPitchMin;
		float fHipGunKickPitchMax;
		float fHipGunKickYawMin;
		float fHipGunKickYawMax;
		float fHipGunKickAccel;
		float fHipGunKickSpeedMax;
		float fHipGunKickSpeedDecay;
		float fHipGunKickStaticDecay;
		float fHipViewKickPitchMin;
		float fHipViewKickPitchMax;
		float fHipViewKickYawMin;
		float fHipViewKickYawMax;
		float fHipViewScatterMin;
		float fHipViewScatterMax;
		float fightDist;
		float maxDist;
		const char* accuracyGraphName[2];
		float(*originalAccuracyGraphKnots[2])[2];
		unsigned __int16 originalAccuracyGraphKnotCount[2];
		int iPositionReloadTransTime;
		float leftArc;
		float rightArc;
		float topArc;
		float bottomArc;
		float accuracy;
		float aiSpread;
		float playerSpread;
		float minTurnSpeed[2];
		float maxTurnSpeed[2];
		float pitchConvergenceTime;
		float yawConvergenceTime;
		float suppressTime;
		float maxRange;
		float fAnimHorRotateInc;
		float fPlayerPositionDist;
		const char* szUseHintString;
		const char* dropHintString;
		int iUseHintStringIndex;
		int dropHintStringIndex;
		float horizViewJitter;
		float vertViewJitter;
		float scanSpeed;
		float scanAccel;
		int scanPauseTime;
		const char* szScript;
		float fOOPosAnimLength[2];
		int minDamage;
		int minPlayerDamage;
		float fMaxDamageRange;
		float fMinDamageRange;
		float destabilizationRateTime;
		float destabilizationCurvatureMax;
		int destabilizeDistance;
		float* locationDamageMultipliers;
		const char* fireRumble;
		const char* meleeImpactRumble;
		TracerDef* tracerType;
		float turretScopeZoomRate;
		float turretScopeZoomMin;
		float turretScopeZoomMax;
		float turretOverheatUpRate;
		float turretOverheatDownRate;
		float turretOverheatPenalty;
		snd_alias_list_t* turretOverheatSound;
		FxEffectDef* turretOverheatEffect;
		const char* turretBarrelSpinRumble;
		float turretBarrelSpinSpeed;
		float turretBarrelSpinUpTime;
		float turretBarrelSpinDownTime;
		snd_alias_list_t* turretBarrelSpinMaxSnd;
		snd_alias_list_t* turretBarrelSpinUpSnd[4];
		snd_alias_list_t* turretBarrelSpinDownSnd[4];
		snd_alias_list_t* missileConeSoundAlias;
		snd_alias_list_t* missileConeSoundAliasAtBase;
		float missileConeSoundRadiusAtTop;
		float missileConeSoundRadiusAtBase;
		float missileConeSoundHeight;
		float missileConeSoundOriginOffset;
		float missileConeSoundVolumescaleAtCore;
		float missileConeSoundVolumescaleAtEdge;
		float missileConeSoundVolumescaleCoreSize;
		float missileConeSoundPitchAtTop;
		float missileConeSoundPitchAtBottom;
		float missileConeSoundPitchTopSize;
		float missileConeSoundPitchBottomSize;
		float missileConeSoundCrossfadeTopSize;
		float missileConeSoundCrossfadeBottomSize;
		bool sharedAmmo;
		bool lockonSupported;
		bool requireLockonToFire;
		bool bigExplosion;
		bool noAdsWhenMagEmpty;
		bool avoidDropCleanup;
		bool inheritsPerks;
		bool crosshairColorChange;
		bool bRifleBullet;
		bool armorPiercing;
		bool bBoltAction;
		bool aimDownSight;
		bool bRechamberWhileAds;
		bool bBulletExplosiveDamage;
		bool bCookOffHold;
		bool bClipOnly;
		bool noAmmoPickup;
		bool adsFireOnly;
		bool cancelAutoHolsterWhenEmpty;
		bool disableSwitchToWhenEmpty;
		bool suppressAmmoReserveDisplay;
		bool laserSightDuringNightvision;
		bool markableViewmodel;
		bool noDualWield;
		bool flipKillIcon;
		bool bNoPartialReload;
		bool bSegmentedReload;
		bool blocksProne;
		bool silenced;
		bool isRollingGrenade;
		bool projExplosionEffectForceNormalUp;
		bool bProjImpactExplode;
		bool stickToPlayers;
		bool hasDetonator;
		bool disableFiring;
		bool timedDetonation;
		bool rotate;
		bool holdButtonToThrow;
		bool freezeMovementWhenFiring;
		bool thermalScope;
		bool altModeSameWeapon;
		bool turretBarrelSpinEnabled;
		bool missileConeSoundEnabled;
		bool missileConeSoundPitchshiftEnabled;
		bool missileConeSoundCrossfadeEnabled;
		bool offhandHoldIsCancelable;
	};

	enum ImpactType
	{
		IMPACT_TYPE_NONE = 0x0,
		IMPACT_TYPE_BULLET_SMALL = 0x1,
		IMPACT_TYPE_BULLET_LARGE = 0x2,
		IMPACT_TYPE_BULLET_AP = 0x3,
		IMPACT_TYPE_BULLET_EXPLODE = 0x4,
		IMPACT_TYPE_SHOTGUN = 0x5,
		IMPACT_TYPE_SHOTGUN_EXPLODE = 0x6,
		IMPACT_TYPE_GRENADE_BOUNCE = 0x7,
		IMPACT_TYPE_GRENADE_EXPLODE = 0x8,
		IMPACT_TYPE_ROCKET_EXPLODE = 0x9,
		IMPACT_TYPE_PROJECTILE_DUD = 0xA,
		IMPACT_TYPE_COUNT = 0xB,
	};

	struct WeaponCompleteDef
	{
		const char* szInternalName;
		WeaponDef* weapDef;
		const char* szDisplayName;
		unsigned __int16* hideTags;
		const char** szXAnims;
		float fAdsZoomFov;
		int iAdsTransInTime;
		int iAdsTransOutTime;
		int iClipSize;
		ImpactType impactType;
		int iFireTime;
		weaponIconRatioType_t dpadIconRatio;
		float penetrateMultiplier;
		float fAdsViewKickCenterSpeed;
		float fHipViewKickCenterSpeed;
		const char* szAltWeaponName;
		unsigned int altWeaponIndex;
		int iAltRaiseTime;
		Material* killIcon;
		Material* dpadIcon;
		int fireAnimLength;
		int iFirstRaiseTime;
		int ammoDropStockMax;
		float adsDofStart;
		float adsDofEnd;
		unsigned __int16 accuracyGraphKnotCount[2];
		float(*accuracyGraphKnots[2])[2];
		bool motionTracker;
		bool enhanced;
		bool dpadIconShowsAmmo;
	};

	struct SndDriverGlobals
	{
		const char* name;
	};

	struct FxImpactEntry
	{
		FxEffectDef* nonflesh[31];
		FxEffectDef* flesh[4];
	};

	struct FxImpactTable
	{
		const char* name;
		FxImpactEntry* table;
	};

	struct RawFile
	{
		const char* name;
		int compressedLen;
		int len;
		const char* buffer;
	};

	struct StringTableCell
	{
		const char* string;
		int hash;
	};

	struct StringTable
	{
		const char* name;
		int columnCount;
		int rowCount;
		StringTableCell* values;
	};

	enum LbColType
	{
		LBCOL_TYPE_NUMBER = 0x0,
		LBCOL_TYPE_TIME = 0x1,
		LBCOL_TYPE_LEVELXP = 0x2,
		LBCOL_TYPE_PRESTIGE = 0x3,
		LBCOL_TYPE_BIGNUMBER = 0x4,
		LBCOL_TYPE_PERCENT = 0x5,
		LBCOL_TYPE_COUNT = 0x6,
	};

	enum LbAggType
	{
		LBAGG_TYPE_MIN = 0x0,
		LBAGG_TYPE_MAX = 0x1,
		LBAGG_TYPE_SUM = 0x2,
		LBAGG_TYPE_LAST = 0x3,
		LBAGG_TYPE_COUNT = 0x4,
	};

	struct LbColumnDef
	{
		const char* name;
		int id;
		int propertyId;
		bool hidden;
		const char* statName;
		LbColType type;
		int precision;
		LbAggType agg;
	};

	struct LeaderboardDef
	{
		const char* name;
		int id;
		int columnCount;
		int xpColId;
		int prestigeColId;
		LbColumnDef* columns;
	};

	struct __declspec(align(4)) StructuredDataEnumEntry
	{
		const char* string;
		unsigned __int16 index;
	};

	struct StructuredDataEnum
	{
		int entryCount;
		int reservedEntryCount;
		StructuredDataEnumEntry* entries;
	};

	enum LookupResultDataType
	{
		LOOKUP_RESULT_INT = 0x0,
		LOOKUP_RESULT_BOOL = 0x1,
		LOOKUP_RESULT_STRING = 0x2,
		LOOKUP_RESULT_FLOAT = 0x3,
		LOOKUP_RESULT_SHORT = 0x4,
	};

	enum LookupState
	{
		LOOKUP_IN_PROGRESS = 0x0,
		LOOKUP_FINISHED = 0x1,
		LOOKUP_ERROR = 0x2,
	};

	enum LookupError
	{
		LOOKUP_ERROR_NONE = 0x0,
		LOOKUP_ERROR_WRONG_DATA_TYPE = 0x1,
		LOOKUP_ERROR_INDEX_OUTSIDE_BOUNDS = 0x2,
		LOOKUP_ERROR_INVALID_STRUCT_PROPERTY = 0x3,
		LOOKUP_ERROR_INVALID_ENUM_VALUE = 0x4,
		LOOKUP_ERROR_COUNT = 0x5,
	};

	enum StructuredDataTypeCategory
	{
		DATA_INT = 0x0,
		DATA_BYTE = 0x1,
		DATA_BOOL = 0x2,
		DATA_STRING = 0x3,
		DATA_ENUM = 0x4,
		DATA_STRUCT = 0x5,
		DATA_INDEXED_ARRAY = 0x6,
		DATA_ENUM_ARRAY = 0x7,
		DATA_FLOAT = 0x8,
		DATA_SHORT = 0x9,
		DATA_COUNT = 0xA,
	};

	union StructuredDataTypeUnion
	{
		unsigned int stringDataLength;
		int enumIndex;
		int structIndex;
		int indexedArrayIndex;
		int enumedArrayIndex;
	};

	struct StructuredDataType
	{
		StructuredDataTypeCategory type;
		StructuredDataTypeUnion u;
	};

	struct StructuredDataStructProperty
	{
		const char* name;
		StructuredDataType type;
		unsigned int offset;
	};

	struct StructuredDataStruct
	{
		int propertyCount;
		StructuredDataStructProperty* properties;
		int size;
		unsigned int bitOffset;
	};

	struct StructuredDataIndexedArray
	{
		int arraySize;
		StructuredDataType elementType;
		unsigned int elementSize;
	};

	struct StructuredDataEnumedArray
	{
		int enumIndex;
		StructuredDataType elementType;
		unsigned int elementSize;
	};

	struct StructuredDataDef
	{
		int version;
		unsigned int formatChecksum;
		int enumCount;
		StructuredDataEnum* enums;
		int structCount;
		StructuredDataStruct* structs;
		int indexedArrayCount;
		StructuredDataIndexedArray* indexedArrays;
		int enumedArrayCount;
		StructuredDataEnumedArray* enumedArrays;
		StructuredDataType rootType;
		unsigned int size;
	};


	struct StructuredDataLookup
	{
		StructuredDataDef* def;
		StructuredDataType* type;
		unsigned int offset;
		LookupError error;
	};

	struct StructuredDataDefSet
	{
		const char* name;
		unsigned int defCount;
		StructuredDataDef* defs;
	};

	struct StructuredDataBuffer
	{
		char* data;
		unsigned int size;
	};

	enum VehicleType
	{
		VEH_WHEELS_4 = 0x0,
		VEH_TANK = 0x1,
		VEH_PLANE = 0x2,
		VEH_BOAT = 0x3,
		VEH_ARTILLERY = 0x4,
		VEH_HELICOPTER = 0x5,
		VEH_SNOWMOBILE = 0x6,
		VEH_TYPE_COUNT = 0x7,
	};

	enum VehicleAxleType
	{
		VEH_AXLE_FRONT = 0x0,
		VEH_AXLE_REAR = 0x1,
		VEH_AXLE_ALL = 0x2,
		VEH_AXLE_COUNT = 0x3,
	};

	struct VehiclePhysDef
	{
		int physicsEnabled;
		const char* physPresetName;
		PhysPreset* physPreset;
		const char* accelGraphName;
		VehicleAxleType steeringAxle;
		VehicleAxleType powerAxle;
		VehicleAxleType brakingAxle;
		float topSpeed;
		float reverseSpeed;
		float maxVelocity;
		float maxPitch;
		float maxRoll;
		float suspensionTravelFront;
		float suspensionTravelRear;
		float suspensionStrengthFront;
		float suspensionDampingFront;
		float suspensionStrengthRear;
		float suspensionDampingRear;
		float frictionBraking;
		float frictionCoasting;
		float frictionTopSpeed;
		float frictionSide;
		float frictionSideRear;
		float velocityDependentSlip;
		float rollStability;
		float rollResistance;
		float pitchResistance;
		float yawResistance;
		float uprightStrengthPitch;
		float uprightStrengthRoll;
		float targetAirPitch;
		float airYawTorque;
		float airPitchTorque;
		float minimumMomentumForCollision;
		float collisionLaunchForceScale;
		float wreckedMassScale;
		float wreckedBodyFriction;
		float minimumJoltForNotify;
		float slipThresholdFront;
		float slipThresholdRear;
		float slipFricScaleFront;
		float slipFricScaleRear;
		float slipFricRateFront;
		float slipFricRateRear;
		float slipYawTorque;
	};

	struct VehicleDef
	{
		const char* name;
		VehicleType type;
		const char* useHintString;
		int health;
		int quadBarrel;
		float texScrollScale;
		float topSpeed;
		float accel;
		float rotRate;
		float rotAccel;
		float maxBodyPitch;
		float maxBodyRoll;
		float fakeBodyAccelPitch;
		float fakeBodyAccelRoll;
		float fakeBodyVelPitch;
		float fakeBodyVelRoll;
		float fakeBodySideVelPitch;
		float fakeBodyPitchStrength;
		float fakeBodyRollStrength;
		float fakeBodyPitchDampening;
		float fakeBodyRollDampening;
		float fakeBodyBoatRockingAmplitude;
		float fakeBodyBoatRockingPeriod;
		float fakeBodyBoatRockingRotationPeriod;
		float fakeBodyBoatRockingFadeoutSpeed;
		float boatBouncingMinForce;
		float boatBouncingMaxForce;
		float boatBouncingRate;
		float boatBouncingFadeinSpeed;
		float boatBouncingFadeoutSteeringAngle;
		float collisionDamage;
		float collisionSpeed;
		float killcamOffset[3];
		int playerProtected;
		int bulletDamage;
		int armorPiercingDamage;
		int grenadeDamage;
		int projectileDamage;
		int projectileSplashDamage;
		int heavyExplosiveDamage;
		VehiclePhysDef vehPhysDef;
		float boostDuration;
		float boostRechargeTime;
		float boostAcceleration;
		float suspensionTravel;
		float maxSteeringAngle;
		float steeringLerp;
		float minSteeringScale;
		float minSteeringSpeed;
		int camLookEnabled;
		float camLerp;
		float camPitchInfluence;
		float camRollInfluence;
		float camFovIncrease;
		float camFovOffset;
		float camFovSpeed;
		const char* turretWeaponName;
		WeaponCompleteDef* turretWeapon;
		float turretHorizSpanLeft;
		float turretHorizSpanRight;
		float turretVertSpanUp;
		float turretVertSpanDown;
		float turretRotRate;
		snd_alias_list_t* turretSpinSnd;
		snd_alias_list_t* turretStopSnd;
		int trophyEnabled;
		float trophyRadius;
		float trophyInactiveRadius;
		int trophyAmmoCount;
		float trophyReloadTime;
		unsigned __int16 trophyTags[4];
		Material* compassFriendlyIcon;
		Material* compassEnemyIcon;
		int compassIconWidth;
		int compassIconHeight;
		snd_alias_list_t* idleLowSnd;
		snd_alias_list_t* idleHighSnd;
		snd_alias_list_t* engineLowSnd;
		snd_alias_list_t* engineHighSnd;
		float engineSndSpeed;
		snd_alias_list_t* engineStartUpSnd;
		int engineStartUpLength;
		snd_alias_list_t* engineShutdownSnd;
		snd_alias_list_t* engineIdleSnd;
		snd_alias_list_t* engineSustainSnd;
		snd_alias_list_t* engineRampUpSnd;
		int engineRampUpLength;
		snd_alias_list_t* engineRampDownSnd;
		int engineRampDownLength;
		snd_alias_list_t* suspensionSoftSnd;
		float suspensionSoftCompression;
		snd_alias_list_t* suspensionHardSnd;
		float suspensionHardCompression;
		snd_alias_list_t* collisionSnd;
		float collisionBlendSpeed;
		snd_alias_list_t* speedSnd;
		float speedSndBlendSpeed;
		const char* surfaceSndPrefix;
		snd_alias_list_t* surfaceSnds[31];
		float surfaceSndBlendSpeed;
		float slideVolume;
		float slideBlendSpeed;
		float inAirPitch;
	};

	struct AddonMapEnts
	{
		const char* name;
		char* entityString;
		int numEntityChars;
		MapTriggers trigger;
	};

	union XAssetHeader
	{
		void* data;
		PhysPreset* physPreset;
		PhysCollmap* physCollmap;
		XAnimParts* parts;
		XModelSurfs* modelSurfs;
		XModel* model;
		Material* material;
		MaterialPixelShader* pixelShader;
		MaterialVertexShader* vertexShader;
		MaterialVertexDeclaration* vertexDecl;
		MaterialTechniqueSet* techniqueSet;
		GfxImage* image;
		snd_alias_list_t* sound;
		SndCurve* sndCurve;
		LoadedSound* loadSnd;
		clipMap_t* clipMap;
		ComWorld* comWorld;
		GameWorldSp* gameWorldSp;
		GameWorldMp* gameWorldMp;
		MapEnts* mapEnts;
		FxWorld* fxWorld;
		GfxWorld* gfxWorld;
		GfxLightDef* lightDef;
		Font_s* font;
		MenuList* menuList;
		menuDef_t* menu;
		LocalizeEntry* localize;
		WeaponCompleteDef* weapon;
		SndDriverGlobals* sndDriverGlobals;
		FxEffectDef* fx;
		FxImpactTable* impactFx;
		RawFile* rawfile;
		StringTable* stringTable;
		LeaderboardDef* leaderboardDef;
		StructuredDataDefSet* structuredDataDefSet;
		TracerDef* tracerDef;
		VehicleDef* vehDef;
		AddonMapEnts* addonMapEnts;
	};

	struct weaponParms
	{
		float forward[3];
		float right[3];
		float up[3];
		float muzzleTrace[3];
		float gunForward[3];
		unsigned int weaponIndex;
		const WeaponDef* weapDef;
		const WeaponCompleteDef* weapCompleteDef;
	};

	struct XAsset
	{
		XAssetType type;
		XAssetHeader header;
	};

	struct XBlock
	{
		char* data;
		unsigned int size;
	};

	struct XAssetEntry
	{
		XAsset asset;
		char zoneIndex;
		volatile char inuseMask;
		bool printedMissingAsset;
		unsigned __int16 nextHash;
		unsigned __int16 nextOverride;
	};

	enum XFileLanguage : unsigned char
	{
		XLANG_NONE = 0x00,
		XLANG_ENGLISH = 0x01,
		XLANG_FRENCH = 0x02,
		XLANG_GERMAN = 0x03,
		XLANG_ITALIAN = 0x04,
		XLANG_SPANISH = 0x05,
		XLANG_BRITISH = 0x06,
		XLANG_RUSSIAN = 0x07,
		XLANG_POLISH = 0x08,
		XLANG_KOREAN = 0x09,
		XLANG_TAIWANESE = 0x0A,
		XLANG_JAPANESE = 0x0B,
		XLANG_CHINESE = 0x0C,
		XLANG_THAI = 0x0D,
		XLANG_LEET = 0x0E, // Wat?
		XLANG_CZECH = 0x0F,
	};

#pragma pack(push, 1)
	struct XFileHeader
	{
		unsigned __int64 magic;
		unsigned int version;
		XFileLanguage language;
		DWORD highDateTime;
		DWORD lowDateTime;
	};
#pragma pack(pop)

	enum XFILE_BLOCK_TYPES
	{
		XFILE_BLOCK_TEMP = 0x0,
		XFILE_BLOCK_PHYSICAL = 0x1,
		XFILE_BLOCK_RUNTIME = 0x2,
		XFILE_BLOCK_VIRTUAL = 0x3,
		XFILE_BLOCK_LARGE = 0x4,

		// Those are probably incorrect
		XFILE_BLOCK_CALLBACK,
		XFILE_BLOCK_VERTEX,
		XFILE_BLOCK_INDEX,

		MAX_XFILE_COUNT,

		XFILE_BLOCK_INVALID = -1
	};

	struct XFile
	{
		unsigned int size;
		unsigned int externalSize;
		unsigned int blockSize[MAX_XFILE_COUNT];
	};

	struct ScriptStringList
	{
		int count;
		const char** strings;
	};

	struct XAssetList
	{
		ScriptStringList stringList;
		int assetCount;
		XAsset* assets;
	};

	struct ZoneHeader
	{
		XFile xFile;
		XAssetList assetList;
	};

	struct XZoneMemory
	{
		XBlock blocks[MAX_XFILE_COUNT];
		char* lockedVertexData;
		char* lockedIndexData;
		void* vertexBuffer;
		void* indexBuffer;
	};

	struct XZone
	{
		int unk;
		char name[64];
		int flags;
		int allocType;
		XZoneMemory mem;
		int fileSize;
		char modZone;
	};

	struct XNKID
	{
		char ab[8];
	};

	struct XNADDR
	{
		in_addr ina;
		in_addr inaOnline;
		unsigned __int16 wPortOnline;
		char abEnet[6];
		char abOnline[20];
	};

	struct XNKEY
	{
		char ab[16];
	};

	struct _XSESSION_INFO
	{
		XNKID sessionID;
		XNADDR hostAddress;
		XNKEY keyExchangeKey;
	};

	struct GfxSunShadowMapMetrics
	{
		unsigned int pixelsPerTile;
		unsigned int tilesPerTexture;
		unsigned int usefulSize;
		unsigned int minCoord;
		float nearClip;
		float farClip;
	};

	struct GfxSunShadowProjectionSetup
	{
		float sunAxis[3][3];
		float nearShadowMinDist;
		float frustumRayDistToEdgeOfNearMap;
		float shadowOrg[2];
		float shadowOrgPixelCenter[2];
		float snappedShadowOrg[2][2];
		float sampleSize[2];
	};

	struct mapArena_t
	{
		char uiName[32];
		char mapName[16];
		char description[32];
		char mapimage[32];
		char keys[32][16];
		char values[32][64];
		char pad[144];
	};

	struct newMapArena_t
	{
		char uiName[32];
		char oldMapName[16];
		char description[32];
		char mapimage[32];
		char keys[32][16];
		char values[32][64];
		char other[144];
		char mapName[32];
	};

	struct gameTypeName_t
	{
		char gameType[12];
		char uiName[32];
	};

	enum fsMode_t
	{
		FS_READ = 0x0,
		FS_WRITE = 0x1,
		FS_APPEND = 0x2,
		FS_APPEND_SYNC = 0x3,
	};

	struct fileInIwd_s
	{
		unsigned int pos;
		char* name;
		fileInIwd_s* next;
	};

	struct iwd_t
	{
		char iwdFilename[MAX_OSPATH];
		char iwdBasename[MAX_OSPATH];
		char iwdGamename[MAX_OSPATH];
		char* handle;
		int checksum;
		int pure_checksum;
		volatile int hasOpenFile;
		int numfiles;
		char referenced;
		unsigned int hashSize;
		fileInIwd_s** hashTable;
		fileInIwd_s* buildBuffer;
};

#ifdef IDA
	typedef void _iobuf;
#endif

	union qfile_gus
	{
		_iobuf* o;
		char* z;
	};

	struct qfile_us
	{
		qfile_gus file;
		int iwdIsClone;
	};

	struct fileHandleData_t
	{
		qfile_us handleFiles;
		int handleSync;
		int fileSize;
		int zipFilePos;
		iwd_t* zipFile;
		int streamed;
		char name[256];
	};

	struct directory_t
	{
		char path[MAX_OSPATH];
		char gamedir[MAX_OSPATH];
	};

	struct searchpath_s
	{
		searchpath_s* next;
		iwd_t* iwd;
		directory_t* dir;
		int bLocalized;
		int ignore;
		int ignorePureCheck;
		int language;
	};

	struct SafeArea
	{
		int fontHeight;
		int textHeight;
		int textWidth;
		float left;
		float top;
		float right;
		float bottom;
	};

#pragma pack(push, 4)
	struct SpawnVar
	{
		bool spawnVarsValid;
		int numSpawnVars;
		char* spawnVars[64][2];
		int numSpawnVarChars;
		char spawnVarChars[2048];
	};
#pragma pack(pop)

	typedef char mapname_t[40];

	struct TraceExtents
	{
		float midPoint[3];
		float halfDelta[3];
		float halfDeltaAbs[3];
		float invDeltaAbs[3];
		float start[3];
		float end[3];
	};

	struct TraceCheckCount
	{
		int global;
		int* partitions;
	};

	struct TraceThreadInfo
	{
		TraceCheckCount checkcount;
	};

	struct CM_WorldTraceCallbacks
	{
		bool(*isGlassSolid)(unsigned int);
	};

	struct traceWork_t
	{
		TraceExtents extents;
		float delta[3];
		float deltaLen;
		float deltaLenSq;
		float delta2DLen;
		float delta2DLenSq;
		float size[3];
		Bounds bounds;
		int contents;
		bool isPoint;
		bool axialCullOnly;
		float radius;
		float offset[3];
		float radiusOffset[3];
		float boundingRadius;
		TraceThreadInfo threadInfo;
		CM_WorldTraceCallbacks* callbacks;
	};

	struct gameState_t
	{
		int stringOffsets[4139];
		char stringData[131072];
		int dataCount;
	};

	struct PrecacheEntry
	{
		unsigned __int16 filename;
		bool include;
		unsigned int sourcePos;
	};

	struct XAnimParent
	{
		unsigned short flags;
		unsigned short children;
	};

	struct XAnimEntry
	{
		unsigned short numAnims;
		unsigned short parent;
		union
		{
			XAnimParts* parts;
			XAnimParent animParent;
		} ___u2;
	};

	struct XAnim_s
	{
		unsigned int size;
		const char* debugName;
		const char** debugAnimNames;
		XAnimEntry entries[1];
	};

	struct HunkUser
	{
		HunkUser* current;
		HunkUser* next;
		int maxSize;
		int end;
		int pos;
		const char* name;
		bool fixed;
		int type;
		char buf[1];
	};

	static_assert(sizeof(HunkUser) == 36);

	struct VariableStackBuffer
	{
		const char* pos;
		unsigned __int16 size;
		unsigned __int16 bufLen;
		unsigned __int16 localId;
		char time;
		char buf[1];
	};

	enum
	{
		VAR_UNDEFINED = 0x0,
		VAR_BEGIN_REF = 0x1,
		VAR_POINTER = 0x1,
		VAR_STRING = 0x2,
		VAR_ISTRING = 0x3,
		VAR_VECTOR = 0x4,
		VAR_END_REF = 0x5,
		VAR_FLOAT = 0x5,
		VAR_INTEGER = 0x6,
		VAR_CODEPOS = 0x7,
		VAR_PRECODEPOS = 0x8,
		VAR_FUNCTION = 0x9,
		VAR_BUILTIN_FUNCTION = 0xA,
		VAR_BUILTIN_METHOD = 0xB,
		VAR_STACK = 0xC,
		VAR_ANIMATION = 0xD,
		VAR_DEVELOPER_CODEPOS = 0xE,
		VAR_PRE_ANIMATION = 0xF,
		VAR_THREAD = 0x10,
		VAR_NOTIFY_THREAD = 0x11,
		VAR_TIME_THREAD = 0x12,
		VAR_CHILD_THREAD = 0x13,
		VAR_OBJECT = 0x14,
		VAR_DEAD_ENTITY = 0x15,
		VAR_ENTITY = 0x16,
		VAR_ARRAY = 0x17,
		VAR_DEAD_THREAD = 0x18,
		VAR_COUNT = 0x19,
		VAR_THREAD_LIST = 0x1A,
		VAR_ENDON_LIST = 0x1B,
	};

	enum
	{
		FIRST_OBJECT = 0x10,
		FIRST_CLEARABLE_OBJECT = 0x14,
		LAST_NONENTITY_OBJECT = 0x14,
		FIRST_ENTITY_OBJECT = 0x16,
		FIRST_NONFIELD_OBJECT = 0x17,
		FIRST_DEAD_OBJECT = 0x18,
	};

	union VariableUnion
	{
		int intValue;
		unsigned int uintValue;
		float floatValue;
		unsigned int stringValue;
		const float* vectorValue;
		const char* codePosValue;
		unsigned int pointerValue;
		VariableStackBuffer* stackValue;
		unsigned int entityOffset;
	};

	struct VariableValue
	{
		VariableUnion u;
		int type;
	};

	struct function_stack_t
	{
		const char* pos;
		unsigned int localId;
		unsigned int localVarCount;
		VariableValue* top;
		VariableValue* startTop;
	};

	struct function_frame_t
	{
		function_stack_t fs;
		int topType;
	};

	struct scrVmPub_t
	{
		unsigned int* localVars;
		VariableValue* maxStack;
		int function_count;
		function_frame_t* function_frame;
		VariableValue* top;
		bool debugCode;
		bool abort_on_error;
		bool terminal_error;
		unsigned int inparamcount;
		unsigned int outparamcount;
		function_frame_t function_frame_start[32];
		VariableValue stack[2048];
	};

	struct scrVarPub_t
	{
		const char* fieldBuffer;
		unsigned __int16 canonicalStrCount;
		bool developer_script;
		bool evaluate;
		const char* error_message;
		int error_index;
		int time;
		int timeArrayId;
		int pauseArrayId;
		int notifyArrayId;
		int objectStackId;
		int levelId;
		int gameId;
		int animId;
		int freeEntList;
		int tempVariable;
		int numScriptValues[2];
		bool bInited;
		unsigned __int16 savecount;
		unsigned __int16 savecountMark;
		int checksum;
		int entId;
		int entFieldName;
		HunkUser* programHunkUser;
		const char* programBuffer;
		const char* endScriptBuffer;
		unsigned __int16 saveIdMap[36864];
		unsigned __int16 saveIdMapRev[36864];
	};

	static_assert(sizeof(scrVarPub_t) == 0x24060);

	struct scrCompilePub_t
	{
		int value_count;
		int far_function_count;
		unsigned int loadedscripts;
		unsigned int scriptsPos;
		unsigned int scriptsCount;
		unsigned int scriptsDefine;
		unsigned int builtinFunc;
		unsigned int builtinMeth;
		unsigned __int16 canonicalStrings[65536];
		const char* in_ptr;
		bool in_ptr_valid;
		const char* parseBuf;
		bool script_loading;
		bool allowedBreakpoint;
		int developer_statement;
		char* opcodePos;
		unsigned int programLen;
		int func_table_size;
		int func_table[1024];
	};

	enum
	{
		SOURCE_TYPE_BREAKPOINT = 0x1,
		SOURCE_TYPE_CALL = 0x2,
		SOURCE_TYPE_CALL_POINTER = 0x4,
		SOURCE_TYPE_THREAD_START = 0x8,
		SOURCE_TYPE_BUILTIN_CALL = 0x10,
		SOURCE_TYPE_NOTIFY = 0x20,
		SOURCE_TYPE_GETFUNCTION = 0x40,
		SOURCE_TYPE_WAIT = 0x80,
	};

	struct OpcodeLookup
	{
		const char* codePos;
		unsigned int sourcePosIndex;
		unsigned __int16 sourcePosCount;
		int profileTime;
		int profileBuiltInTime;
		int profileUsage;
	};

	static_assert(sizeof(OpcodeLookup) == 24);

	struct SourceLookup
	{
		unsigned int sourcePos;
		int type;
	};

	struct SaveSourceBufferInfo
	{
		char* buf;
		char* sourceBuf;
		int len;
	};

	struct scrParserGlob_t
	{
		OpcodeLookup* opcodeLookup;
		unsigned int opcodeLookupMaxSize;
		unsigned int opcodeLookupLen;
		SourceLookup* sourcePosLookup;
		unsigned int sourcePosLookupMaxSize;
		unsigned int sourcePosLookupLen;
		unsigned int sourceBufferLookupMaxSize;
		const char* currentCodePos;
		unsigned int currentSourcePosCount;
		SaveSourceBufferInfo* saveSourceBufferLookup;
		unsigned int saveSourceBufferLookupLen;
		int delayedSourceIndex;
		int threadStartSourceIndex;
	};

	struct SourceBufferInfo
	{
		const char* codePos;
		char* buf;
		const char* sourceBuf;
		int len;
		int sortedIndex;
		bool archive;
		int time;
		int avgTime;
		int maxTime;
		float totalTime;
		float totalBuiltIn;
	};

	struct scrParserPub_t
	{
		SourceBufferInfo* sourceBufferLookup;
		unsigned int sourceBufferLookupLen;
		const char* scriptfilename;
		const char* sourceBuf;
	};

	struct scr_animtree_t
	{
		XAnim_s* anims;
	};

	struct scrMemTreePub_t
	{
		char* mt_buffer;
	};

	struct scrAnimPub_t
	{
		unsigned int animtrees;
		unsigned int animtree_node;
		unsigned int animTreeNames;
		scr_animtree_t xanim_lookup[2][128];
		unsigned int xanim_num[2];
		unsigned int animTreeIndex;
		bool animtree_loading;
	};

	struct scr_localVar_t
	{
		unsigned int name;
		unsigned int sourcePos;
	};

	struct scr_block_t
	{
		int abortLevel;
		int localVarsCreateCount;
		int localVarsPublicCount;
		int localVarsCount;
		char localVarsInitBits[8];
		scr_localVar_t localVars[64];
	};

	union sval_u
	{
		int type;
		unsigned int stringValue;
		unsigned int idValue;
		float floatValue;
		int intValue;
		sval_u* node;
		unsigned int sourcePosValue;
		const char* codePosValue;
		const char* debugString;
		scr_block_t* block;
	};

	static_assert(sizeof(sval_u) == 0x4);

	struct stype_t
	{
		sval_u val;
		unsigned int pos;
	};

	static_assert(sizeof(stype_t) == 0x8);

	struct scr_const_t
	{
		scr_string_t _;
		scr_string_t active;
		scr_string_t aim_bone;
		scr_string_t aim_highest_bone;
		scr_string_t aim_vis_bone;
		scr_string_t all;
		scr_string_t allies;
		scr_string_t angles;
		scr_string_t auto_ai;
		scr_string_t auto_nonai;
		scr_string_t axis;
		scr_string_t back;
		scr_string_t bad_guys;
		scr_string_t bad_path;
		scr_string_t begin_firing;
		scr_string_t begin_firing_left;
		scr_string_t cancel_location;
		scr_string_t chest;
		scr_string_t confirm_location;
		scr_string_t crouch;
		scr_string_t current;
		scr_string_t damage;
		scr_string_t dead;
		scr_string_t death;
		scr_string_t deathshield;
		scr_string_t detonate;
		scr_string_t direct;
		scr_string_t dlight;
		scr_string_t done;
		scr_string_t empty;
		scr_string_t empty_offhand;
		scr_string_t offhand_end;
		scr_string_t end_firing;
		scr_string_t end_firing_left;
		scr_string_t entity;
		scr_string_t explode;
		scr_string_t failed;
		scr_string_t first_person;
		scr_string_t forward;
		scr_string_t fraction;
		scr_string_t free;
		scr_string_t goal;
		scr_string_t goal_changed;
		scr_string_t goal_yaw;
		scr_string_t grenade;
		scr_string_t grenadedanger;
		scr_string_t grenade_fire;
		scr_string_t glass_destroyed;
		scr_string_t missile_fire;
		scr_string_t grenade_pullback;
		scr_string_t missile_stuck;
		scr_string_t info_notnull;
		scr_string_t invisible;
		scr_string_t key1;
		scr_string_t key2;
		scr_string_t killanimscript;
		scr_string_t left;
		scr_string_t light;
		scr_string_t manual;
		scr_string_t manual_ai;
		scr_string_t movedone;
		scr_string_t none;
		scr_string_t normal;
		scr_string_t origin;
		scr_string_t other;
		scr_string_t player;
		scr_string_t physics_finished;
		scr_string_t position;
		scr_string_t projectile_impact;
		scr_string_t prone;
		scr_string_t right;
		scr_string_t reload;
		scr_string_t reload_start;
		scr_string_t result;
		scr_string_t reverse;
		scr_string_t rocket;
		scr_string_t rotatedone;
		scr_string_t script_brushmodel;
		scr_string_t script_model;
		scr_string_t script_origin;
		scr_string_t sentry;
		scr_string_t sentry_offline;
		scr_string_t snd_enveffectsprio_level;
		scr_string_t snd_enveffectsprio_shellshock;
		scr_string_t snd_channelvolprio_holdbreath;
		scr_string_t snd_channelvolprio_pain;
		scr_string_t snd_channelvolprio_shellshock;
		scr_string_t spawned;
		scr_string_t stand;
		scr_string_t suppression;
		scr_string_t suppression_end;
		scr_string_t surfacetype;
		scr_string_t tag_aim;
		scr_string_t tag_aim_animated;
		scr_string_t tag_aim_pivot;
		scr_string_t tag_brass;
		scr_string_t tag_butt;
		scr_string_t tag_clip;
		scr_string_t tag_eye;
		scr_string_t tag_flash;
		scr_string_t tag_flash_silenced;
		scr_string_t tag_flash_11;
		scr_string_t tag_flash_2;
		scr_string_t tag_flash_22;
		scr_string_t tag_flash_3;
		scr_string_t tag_fx;
		scr_string_t tag_inhand;
		scr_string_t tag_knife_fx;
		scr_string_t tag_laser;
		scr_string_t tag_origin;
		scr_string_t tag_weapon;
		scr_string_t tag_player;
		scr_string_t tag_camera;
		scr_string_t tag_weapon_left;
		scr_string_t tag_weapon_right;
		scr_string_t tag_weapon_chest;
		scr_string_t tag_stowed_back;
		scr_string_t tag_gasmask;
		scr_string_t tag_gasmask2;
		scr_string_t tag_sync;
		scr_string_t tag_motion_tracker_tl;
		scr_string_t tag_motion_tracker_bl;
		scr_string_t tag_motion_tracker_br;
		scr_string_t tag_motion_tracker_fx;
		scr_string_t tag_reticle_acog;
		scr_string_t tag_reticle_red_dot;
		scr_string_t tag_reticle_tavor_scope;
		scr_string_t tag_reticle_thermal_scope;
		scr_string_t tag_eotech_reticle;
		scr_string_t target_script_trigger;
		scr_string_t third_person;
		scr_string_t top;
		scr_string_t touch;
		scr_string_t trigger;
		scr_string_t trigger_use;
		scr_string_t trigger_use_touch;
		scr_string_t trigger_damage;
		scr_string_t truck_cam;
		scr_string_t weapon_change;
		scr_string_t weapon_fired;
		scr_string_t weapon_switch_started;
		scr_string_t weapon_taken;
		scr_string_t weapon_dropped;
		scr_string_t worldspawn;
		scr_string_t flashbang;
		scr_string_t flash;
		scr_string_t smoke;
		scr_string_t frag;
		scr_string_t throwingknife;
		scr_string_t night_vision_on;
		scr_string_t night_vision_off;
		scr_string_t mod_unknown;
		scr_string_t mod_pistol_bullet;
		scr_string_t mod_rifle_bullet;
		scr_string_t mod_explosive_bullet;
		scr_string_t mod_grenade;
		scr_string_t mod_grenade_splash;
		scr_string_t mod_projectile;
		scr_string_t mod_projectile_splash;
		scr_string_t mod_melee;
		scr_string_t mod_head_shot;
		scr_string_t mod_crush;
		scr_string_t mod_falling;
		scr_string_t mod_suicide;
		scr_string_t mod_trigger_hurt;
		scr_string_t mod_explosive;
		scr_string_t mod_impact;
		scr_string_t script_vehicle;
		scr_string_t script_vehicle_collision;
		scr_string_t script_vehicle_collmap;
		scr_string_t script_vehicle_corpse;
		scr_string_t turret_deactivate;
		scr_string_t turret_fire;
		scr_string_t turret_no_vis;
		scr_string_t turret_not_on_target;
		scr_string_t turret_on_target;
		scr_string_t turret_on_vistarget;
		scr_string_t turret_pitch_clamped;
		scr_string_t turret_rotate_stopped;
		scr_string_t turret_yaw_clamped;
		scr_string_t turretstatechange;
		scr_string_t turretownerchange;
		scr_string_t reached_end_node;
		scr_string_t reached_wait_node;
		scr_string_t reached_wait_speed;
		scr_string_t near_goal;
		scr_string_t tag_wheel_front_left;
		scr_string_t tag_wheel_front_right;
		scr_string_t tag_wheel_back_left;
		scr_string_t tag_wheel_back_right;
		scr_string_t tag_wheel_middle_left;
		scr_string_t tag_wheel_middle_right;
		scr_string_t tag_detach;
		scr_string_t tag_popout;
		scr_string_t tag_body;
		scr_string_t tag_turret;
		scr_string_t tag_turret_base;
		scr_string_t tag_barrel;
		scr_string_t front_left;
		scr_string_t front_right;
		scr_string_t back_left;
		scr_string_t back_right;
		scr_string_t middle_left;
		scr_string_t middle_right;
		scr_string_t veh_boatbounce;
		scr_string_t veh_collision;
		scr_string_t veh_predictedcollision;
		scr_string_t veh_leftground;
		scr_string_t veh_landed;
		scr_string_t veh_jolt;
		scr_string_t vehicle_mount;
		scr_string_t vehicle_dismount;
		scr_string_t constrained;
		scr_string_t follow;
		scr_string_t j_head;
		scr_string_t j_neck;
		scr_string_t thermal;
		scr_string_t primary;
		scr_string_t offhand;
		scr_string_t item;
		scr_string_t altmode;
		scr_string_t exclusive;
		scr_string_t scavenger;
		scr_string_t primaryoffhand;
		scr_string_t secondaryoffhand;
		scr_string_t actionslot1;
		scr_string_t actionslot2;
		scr_string_t actionslot3;
		scr_string_t actionslot4;
		scr_string_t back_low;
		scr_string_t back_mid;
		scr_string_t back_up;
		scr_string_t pelvis;
		scr_string_t auto_change;
		scr_string_t begin;
		scr_string_t call_vote;
		scr_string_t freelook;
		scr_string_t intermission;
		scr_string_t j_mainroot;
		scr_string_t manual_change;
		scr_string_t menuresponse;
		scr_string_t pistol;
		scr_string_t plane_waypoint;
		scr_string_t playing;
		scr_string_t spectator;
		scr_string_t spectating_cycle;
		scr_string_t vote;
		scr_string_t sprint_begin;
		scr_string_t sprint_end;
		scr_string_t normal_radar;
		scr_string_t fast_radar;
		scr_string_t tag_engine_left;
		scr_string_t tag_engine_right;
		scr_string_t slowmo_active;
		scr_string_t slowmo_passive;
	};

	static_assert(sizeof(scr_const_t) == 0x1FE);

	enum UILocalVarType
	{
		UILOCALVAR_INT = 0x0,
		UILOCALVAR_FLOAT = 0x1,
		UILOCALVAR_STRING = 0x2,
	};

	struct UILocalVar
	{
		UILocalVarType type;
		const char* name;
		union
		{
			int integer;
			float value;
			const char* string;
		} u;
	};

	struct UILocalVarContext
	{
		UILocalVar table[256];
	};

	struct UiContext
	{
		int localClientNum;
		float bias;
		int realTime;
		int frameTime;
		struct
		{
			float x;
			float y;
			int lastMoveTime;
		} cursor;
		int isCursorVisible;
		int paintFull;
		int screenWidth;
		int screenHeight;
		float screenAspect;
		float FPS;
		float blurRadiusOut;
		menuDef_t* Menus[640];
		int menuCount;
		menuDef_t* menuStack[16];
		int openMenuCount;
		UILocalVarContext localVars;
	};

	struct msg_t
	{
		int overflowed;
		int readOnly;
		unsigned char* data;
		unsigned char* splitData;
		int maxsize;
		int cursize;
		int splitSize;
		int readcount;
		int bit;
		int lastEntityRef;
	};

	struct XZoneInfo
	{
		const char* name;
		int allocFlags;
		int freeFlags;
	};

	enum FsListBehavior_e
	{
		FS_LIST_PURE_ONLY = 0x0,
		FS_LIST_ALL = 0x1,
	};

	enum svc_ops_e
	{
		svc_nop = 0x0,
		svc_gamestate = 0x1,
		svc_configstring = 0x2,
		svc_serverCommand = 0x3,
		svc_matchdata = 0x4,
		svc_snapshot = 0x5,
		svc_EOF = 0x6,
	};

	enum netsrc_t
	{
		NS_CLIENT1 = 0x0,
		NS_SERVER = 0x1,
		NS_MAXCLIENTS = 0x1,
		NS_PACKET = 0x2,
	};

	enum netadrtype_t
	{
		NA_BOT = 0x0,
		NA_BAD = 0x1,
		NA_LOOPBACK = 0x2,
		NA_BROADCAST = 0x3,
		NA_IP = 0x4,
		NA_IPX = 0x5,
		NA_BROADCAST_IPX = 0x6,
	};

	typedef union
	{
		unsigned char bytes[4];
		std::uint32_t full;
	} netIP_t;

	struct netadr_t
	{
		netadrtype_t type;
		netIP_t ip;
		unsigned __int16 port;
		char ipx[10];
	};

	static_assert(sizeof(netadr_t) == 20);

	struct netProfileInfo_t
	{
		char __pad0[0x5E0];
	};

	static_assert(sizeof(netProfileInfo_t) == 0x5E0);

	struct netchan_t
	{
		int outgoingSequence;
		netsrc_t sock;
		int dropped;
		int incomingSequence;
		netadr_t remoteAddress;
		int qport;
		int fragmentSequence;
		int fragmentLength;
		char* fragmentBuffer;
		int fragmentBufferSize;
		int unsentFragments;
		int unsentFragmentStart;
		int unsentLength;
		char* unsentBuffer;
		int unsentBufferSize;
		netProfileInfo_t prof;
	};

	static_assert(sizeof(netchan_t) == 0x62C);

	struct FxEditorElemAtlas
	{
		int behavior;
		int index;
		int fps;
		int loopCount;
		int colIndexBits;
		int rowIndexBits;
		int entryCount;
	};

	struct FxCurve
	{
		int dimensionCount;
		int keyCount;
		float keys[1];
	};

	struct FxEditorTrailDef
	{
		FxTrailVertex verts[64];
		int vertCount;
		unsigned __int16 inds[128];
		int indCount;
	};

	struct FxEditorElemDef
	{
		char name[48];
		int editorFlags;
		int flags;
		FxFloatRange spawnRange;
		FxFloatRange fadeInRange;
		FxFloatRange fadeOutRange;
		float spawnFrustumCullRadius;
		FxSpawnDefLooping spawnLooping;
		FxSpawnDefOneShot spawnOneShot;
		FxIntRange spawnDelayMsec;
		FxIntRange lifeSpanMsec;
		FxFloatRange spawnOrigin[3];
		FxFloatRange spawnOffsetRadius;
		FxFloatRange spawnOffsetHeight;
		FxFloatRange spawnAngles[3];
		FxFloatRange angularVelocity[3];
		FxFloatRange initialRotation;
		FxFloatRange gravity;
		FxFloatRange elasticity;
		FxEditorElemAtlas atlas;
		float velScale[2][3];
		FxCurve* velShape[2][3][2];
		float rotationScale;
		FxCurve* rotationShape[2];
		float sizeScale[2];
		FxCurve* sizeShape[2][2];
		float scaleScale;
		FxCurve* scaleShape[2];
		FxCurve* color[2];
		FxCurve* alpha[2];
		float lightingFrac;
		float decalFadeInTime;
		float collOffset[3];
		float collRadius;
		FxEffectDef* effectOnImpact;
		FxEffectDef* effectOnDeath;
		int sortOrder;
		FxEffectDef* emission;
		FxFloatRange emitDist;
		FxFloatRange emitDistVariance;
		char elemType;
		int visualCount;
		union
		{
			FxElemVisuals visuals[32];
			FxElemMarkVisuals markVisuals[16];
		} ___u42;
		int trailSplitDist;
		int trailSplitArcDist;
		int trailSplitTime;
		int trailRepeatDist;
		float trailScrollTime;
		FxEditorTrailDef trailDef;
		float sparkFountainGravity;
		float sparkFountainBounceFrac;
		float sparkFountainBounceRand;
		float sparkFountainSparkSpacing;
		float sparkFountainSparkLength;
		int sparkFountainSparkCount;
		float sparkFountainLoopTime;
		float sparkFountainVelMin;
		float sparkFountainVelMax;
		float sparkFountainVelConeAngle;
		float sparkFountainRestSpeed;
		float sparkFountainBoostTime;
		float sparkFountainBoostFactor;
	};

	struct FxEditorEffectDef
	{
		char name[MAX_QPATH];
		int elemCount;
		FxEditorElemDef elems[32];
	};

	struct FxElemField
	{
		const char* keyName;
		bool(__cdecl* handler)(const char**, FxEditorElemDef*);
	};

	enum $18B36A54AD92993D0728595D3504B7CB
	{
		FX_ELEM_TYPE_SPRITE_BILLBOARD = 0x0,
		FX_ELEM_TYPE_SPRITE_ORIENTED = 0x1,
		FX_ELEM_TYPE_TAIL = 0x2,
		FX_ELEM_TYPE_TRAIL = 0x3,
		FX_ELEM_TYPE_CLOUD = 0x4,
		FX_ELEM_TYPE_SPARK_CLOUD = 0x5,
		FX_ELEM_TYPE_SPARK_FOUNTAIN = 0x6,
		FX_ELEM_TYPE_MODEL = 0x7,
		FX_ELEM_TYPE_OMNI_LIGHT = 0x8,
		FX_ELEM_TYPE_SPOT_LIGHT = 0x9,
		FX_ELEM_TYPE_SOUND = 0xA,
		FX_ELEM_TYPE_DECAL = 0xB,
		FX_ELEM_TYPE_RUNNER = 0xC,
		FX_ELEM_TYPE_COUNT = 0xD,
		FX_ELEM_TYPE_LAST_SPRITE = 0x3,
		FX_ELEM_TYPE_LAST_DRAWN = 0x9,
	};

	struct infoParm_t
	{
		char* name;
		int clearSolid;
		int surfaceFlags;
		int contents;
		int toolFlags;
	};

	struct GfxImageFileHeader
	{
		char tag[3];
		char version;
		unsigned int flags;
		char format;
		char unused;
		__int16 dimensions[3];
		int fileSizeForPicmip[4];
	};

	enum $1FA877C9772E9F0892A93F52A91453E9
	{
		MAPTYPE_NONE = 0x0,
		MAPTYPE_INVALID1 = 0x1,
		MAPTYPE_1D = 0x2,
		MAPTYPE_2D = 0x3,
		MAPTYPE_3D = 0x4,
		MAPTYPE_CUBE = 0x5,
		MAPTYPE_COUNT = 0x6,
	};

	enum GfxImageFileFormat
	{
		IMG_FORMAT_INVALID = 0x0,
		IMG_FORMAT_BITMAP_RGBA = 0x1,
		IMG_FORMAT_BITMAP_RGB = 0x2,
		IMG_FORMAT_BITMAP_LUMINANCE_ALPHA = 0x3,
		IMG_FORMAT_BITMAP_LUMINANCE = 0x4,
		IMG_FORMAT_BITMAP_ALPHA = 0x5,
		IMG_FORMAT_WAVELET_RGBA = 0x6,
		IMG_FORMAT_WAVELET_RGB = 0x7,
		IMG_FORMAT_WAVELET_LUMINANCE_ALPHA = 0x8,
		IMG_FORMAT_WAVELET_LUMINANCE = 0x9,
		IMG_FORMAT_WAVELET_ALPHA = 0xA,
		IMG_FORMAT_DXT1 = 0xB,
		IMG_FORMAT_DXT3 = 0xC,
		IMG_FORMAT_DXT5 = 0xD,
		IMG_FORMAT_DXN = 0xE,
		IMG_FORMAT_DXT3A_AS_LUMINANCE = 0xF,
		IMG_FORMAT_DXT5A_AS_LUMINANCE = 0x10,
		IMG_FORMAT_DXT3A_AS_ALPHA = 0x11,
		IMG_FORMAT_DXT5A_AS_ALPHA = 0x12,
		IMG_FORMAT_DXT1_AS_LUMINANCE_ALPHA = 0x13,
		IMG_FORMAT_DXN_AS_LUMINANCE_ALPHA = 0x14,
		IMG_FORMAT_DXT1_AS_LUMINANCE = 0x15,
		IMG_FORMAT_DXT1_AS_ALPHA = 0x16,
		IMG_FORMAT_COUNT = 0x17,
	};

	enum XAnimPartType
	{
		PART_TYPE_NO_QUAT = 0x0,
		PART_TYPE_HALF_QUAT = 0x1,
		PART_TYPE_FULL_QUAT = 0x2,
		PART_TYPE_HALF_QUAT_NO_SIZE = 0x3,
		PART_TYPE_FULL_QUAT_NO_SIZE = 0x4,
		PART_TYPE_SMALL_TRANS = 0x5,
		PART_TYPE_TRANS = 0x6,
		PART_TYPE_TRANS_NO_SIZE = 0x7,
		PART_TYPE_NO_TRANS = 0x8,
		PART_TYPE_ALL = 0x9,
		PART_TYPE_COUNT = 0xA,
	};

	enum $EDD38D6A57EF43793B1F773859FC039A
	{
		FS_SEEK_CUR = 0x0,
		FS_SEEK_END = 0x1,
		FS_SEEK_SET = 0x2,
	};

#pragma region CUSTOM

	enum itemTextStyle
	{
		ITEM_TEXTSTYLE_NORMAL = 0,   // normal text
		ITEM_TEXTSTYLE_SHADOWED = 3,   // drop shadow ( need a color for this )
		ITEM_TEXTSTYLE_SHADOWEDMORE = 6,   // drop shadow ( need a color for this )
		ITEM_TEXTSTYLE_BORDERED = 7,   // border (stroke)
		ITEM_TEXTSTYLE_BORDEREDMORE = 8,   // more border :P
		ITEM_TEXTSTYLE_MONOSPACE = 128,
		ITEM_TEXTSTYLE_MONOSPACESHADOWED = 132,
	};

	enum
	{
		DB_ZONE_CODE_LOC = 0x0,
		DB_ZONE_COMMON_LOC = 0x1,
		DB_ZONE_CODE = 0x2,
		DB_ZONE_COMMON = 0x4,
		DB_ZONE_GAME = 0x8,
		DB_ZONE_MOD = 0x10,
		DB_ZONE_LOAD = 0x20,
		DB_ZONE_DEV = 0x40
	};

	enum
	{
		CF_BIT_NOCLIP = (1 << 0),
		CF_BIT_UFO = (1 << 1),
		CF_BIT_FROZEN = (1 << 2),
		CF_BIT_DISABLE_USABILITY = (1 << 3),
		CF_BIT_NO_KNOCKBACK = (1 << 4),
	};

	enum sessionState_t
	{
		SESS_STATE_PLAYING = 0x0,
		SESS_STATE_DEAD = 0x1,
		SESS_STATE_SPECTATOR = 0x2,
		SESS_STATE_INTERMISSION = 0x3
	};

	enum clientConnected_t
	{
		CON_DISCONNECTED = 0x0,
		CON_CONNECTING = 0x1,
		CON_CONNECTED = 0x2
	};

	enum visionSetMode_t
	{
		VISIONSET_NORMAL,
		VISIONSET_NIGHT,
		VISIONSET_MISSILECAM,
		VISIONSET_THERMAL,
		VISIONSET_PAIN,
		VISIONSETCOUNT
	};

	enum hintType_t
	{
		HINT_NONE = 0x0,
		HINT_NOICON = 0x1,
		HINT_ACTIVATE = 0x2,
		HINT_HEALTH = 0x3,
		HINT_FRIENDLY = 0x4,
		FIRST_WEAPON_HINT = 0x5,
		LAST_WEAPON_HINT = 0x57C,
		HINT_NUM_HINTS = 0x57D,
	};

	struct playerTeamState_t
	{
		int location;
	};

	struct clientSession_t
	{
		sessionState_t sessionState;
		int forceSpectatorClient;
		int killCamEntity;
		int killCamLookAtEntity;
		int status_icon;
		int archiveTime;
		int score;
		int deaths;
		int kills;
		int assists;
		unsigned __int16 scriptPersId;
		clientConnected_t connected;
		usercmd_s cmd;
		usercmd_s oldcmd;
		int localClient;
		int predictItemPickup;
		char newnetname[16];
		int maxHealth;
		int enterTime;
		playerTeamState_t teamState;
		int voteCount;
		int teamVoteCount;
		float moveSpeedScaleMultiplier;
		int viewmodelIndex;
		int noSpectate;
		int teamInfo;
		clientState_s cs;
		int psOffsetTime;
		int hasRadar;
		int isRadarBlocked;
		int radarMode;
		int weaponHudIconOverrides[6];
		unsigned int unusableEntFlags[64];
		float spectateDefaultPos[3];
		float spectateDefaultAngles[3];
	};

	struct gclient_s
	{
		playerState_s ps;
		clientSession_t sess;
		int flags; // 13204
		int spectatorClient;
		int lastCmdTime;
		int buttons;
		int oldbuttons; // 13220
		int latched_buttons; // 13224
		int buttonsSinceLastFrame; // 13228
		unsigned char __pad3[324]; // 13232
		int visionDuration[5];
		char visionName[5][64];
		int lastStand;
		int lastStandTime;
		int hudElemLastAssignedSoundID;
		float lockedTargetOffset[3];
		unsigned __int16 attachShieldTagName;
		hintType_t hintForcedType;
		int hintForcedString;
	};

	static_assert(sizeof(gclient_s) == 0x366C);

	struct EntHandle
	{
		unsigned __int16 number;
		unsigned __int16 infoIndex;
	};

	struct entityShared_t
	{
		char isLinked;
		char modelType;
		char svFlags;
		char isInUse;
		Bounds box;
		int contents;
		Bounds absBox;
		float currentOrigin[3];
		float currentAngles[3];
		EntHandle ownerNum;
		int eventTime;
	};

	enum EntHandler
	{
		ENT_HANDLER_NULL = 0x0,
		ENT_HANDLER_TRIGGER_MULTIPLE = 0x1,
		ENT_HANDLER_TRIGGER_HURT = 0x2,
		ENT_HANDLER_TRIGGER_HURT_TOUCH = 0x3,
		ENT_HANDLER_TRIGGER_DAMAGE = 0x4,
		ENT_HANDLER_SCRIPT_MOVER = 0x5,
		ENT_HANDLER_SCRIPT_MODEL = 0x6,
		ENT_HANDLER_GRENADE = 0x7,
		ENT_HANDLER_TIMED_OBJECT = 0x8,
		ENT_HANDLER_ROCKET = 0x9,
		ENT_HANDLER_CLIENT = 0xA,
		ENT_HANDLER_CLIENT_SPECTATOR = 0xB,
		ENT_HANDLER_CLIENT_DEAD = 0xC,
		ENT_HANDLER_PLAYER_CLONE = 0xD,
		ENT_HANDLER_TURRET_INIT = 0xE,
		ENT_HANDLER_TURRET = 0xF,
		ENT_HANDLER_DROPPED_ITEM = 0x10,
		ENT_HANDLER_ITEM_INIT = 0x11,
		ENT_HANDLER_ITEM = 0x12,
		ENT_HANDLER_PRIMARY_LIGHT = 0x13,
		ENT_HANDLER_PLAYER_BLOCK = 0x14,
		ENT_HANDLER_VEHICLE = 0x15,

		ENT_HANDLER_COUNT
	};

	struct item_ent_t
	{
		int ammoCount;
		int clipAmmoCount;
		int index;
		char dualWieldItem;
		char padding[3];
	};

	struct spawner_ent_t
	{
		int team;
		int timestamp;
		int index;
	};

	struct trigger_ent_t
	{
		int threshold;
		int accumulate;
		int timestamp;
		int singleUserEntIndex;
		char requireLookAt;
		char padding[3];
	};

	struct mover_positions_t
	{
		float decelTime;
		float speed;
		float midTime;
		vec3_t pos1;
		vec3_t pos2;
		vec3_t pos3;
	};

	struct mover_slidedata_t
	{
		Bounds bounds;
		vec3_t velocity;
	};

	union mover_data_t
	{
		mover_positions_t pos;
		mover_slidedata_t slide;
	};

	struct mover_ent_t
	{
		mover_data_t moverData;
		mover_positions_t angle;
	};

	struct corpse_ent_t
	{
		int deathAnimStartTime;
	};

	struct missile_fields_grenade
	{
		float wobbleCycle;
		float curve;
	};

	enum MissileStage
	{
		MISSILESTAGE_SOFTLAUNCH = 0x0,
		MISSILESTAGE_ASCENT = 0x1,
		MISSILESTAGE_DESCENT = 0x2,
	};

	struct missile_fields_nonGrenade
	{
		vec3_t curvature;
		vec3_t targetEntOffset;
		vec3_t targetPos;
		vec3_t launchOrigin;
		MissileStage stage;
	};

	union missile_data_t
	{
		missile_fields_grenade grenade;
		missile_fields_nonGrenade nonGrenade;
	};

	struct missile_ent_t
	{
		int time;
		int timeOfBirth;
		int travelDist;
		vec3_t surfaceNormal;
		team_t team;
		int flags;
		int antilagTimeOffset;
		missile_data_t missileData;
	};

	struct blend_ent_t
	{
		vec3_t pos;
		vec3_t vel;
		vec4_t viewQuat;
		char changed;
		char padding[3];
		float accelTime;
		float decelTime;
		float startTime;
		float totalTime;
	};

	union entity_data_t
	{
		item_ent_t item[2];
		spawner_ent_t spawner;
		trigger_ent_t trigger;
		mover_ent_t mover;
		corpse_ent_t corpse;
		missile_ent_t missile;
		blend_ent_t blend;
	};

	struct gentity_s
	{
		entityState_s s;
		entityShared_t r;
		gclient_s* client; // 344
		void /*Turret*/* turret;
		void /*Vehicle*/* vehicle;
		int physObjId;
		unsigned __int16 model;
		unsigned char physicsObject;
		unsigned char takedamage;
		unsigned char active;
		unsigned char handler;
		unsigned char team;
		bool freeAfterEvent;
		__int16 padding_short;
		unsigned __int16 classname;
		unsigned __int16 script_classname;
		unsigned __int16 script_linkName;
		unsigned __int16 target;
		unsigned __int16 targetname;
		unsigned int attachIgnoreCollision;
		int spawnflags;
		int flags;
		int eventTime;
		int clipmask;
		int processedFrame;
		EntHandle parent;
		int nextthink;
		int health;
		int maxHealth;
		int damage;
		int count;
		entity_data_t entData;
		EntHandle missileTargetEnt;
		EntHandle remoteControlledOwner;
		int tagInfo;
		gentity_s* tagChildren;
		unsigned __int16 attachModelNames[19];
		unsigned __int16 attachTagNames[19];
		int useCount;
		gentity_s* nextFree;
		int birthTime;
	};

	static_assert(sizeof(gentity_s) == 0x274);

	enum
	{
		ENTFIELD_ENTITY = 0x0,
		ENTFIELD_SENTIENT = 0x2000,
		ENTFIELD_ACTOR = 0x4000,
		ENTFIELD_CLIENT = 0x6000,
		ENTFIELD_VEHICLE = 0x8000,
		ENTFIELD_MASK = 0xE000,
	};

	enum fieldtype_t
	{
		F_INT = 0x0,
		F_SHORT = 0x1,
		F_BYTE = 0x2,
		F_FLOAT = 0x3,
		F_CSTRING = 0x4,
		F_STRING = 0x5,
		F_VECTOR = 0x6,
		F_ENTITY = 0x7,
		F_ENTHANDLE = 0x8,
		F_ANGLES_YAW = 0x9,
		F_OBJECT = 0xA,
		F_MODEL = 0xB,
	};

	struct ent_field_t
	{
		const char* name;
		int ofs;
		fieldtype_t type;
		void(*setter)(gentity_s*, int);
		void(*getter)(gentity_s*, int);
	};

	struct client_fields_s
	{
		const char* name;
		int ofs;
		fieldtype_t type;
		void(*setter)(gclient_s*, const client_fields_s*);
		void(*getter)(gclient_s*, const client_fields_s*);
	};

	typedef void(*ScriptCallbackEnt)(gentity_s*, int);
	typedef void(*ScriptCallbackClient)(gclient_s*, const client_fields_s*);

	struct lockonFireParms
	{
		bool lockon;
		gentity_s* target;
		float targetPosOrOffset[3];
		bool topFire;
	};

	struct clientHeader_t
	{
		int state;
		int sendAsActive;
		int deltaMessage;
		int rateDelayed;
		int hasAckedBaselineData;
		int hugeSnapshotSent;
		netchan_t netchan;
		float predictedOrigin[3];
		int predictedOriginServerTime;
		int migrationState;
	};

	static_assert(sizeof(clientHeader_t) == 1624);

	struct svscmd_info_t
	{
		char cmd[1024];
		int time;
		int type;
	};

	struct clientSnapshot_t
	{
		playerState_s ps;
		int num_entities;
		int num_clients;
		int first_entity;
		int first_client;
		int messageSent;
		int messageAcked;
		int messageSize;
		int serverTime;
		int timeDelta;
		int baselineSnap;
	};

	struct client_s
	{
		clientHeader_t header;
		const char* dropReason; // 1624
		char userinfo[1024]; // 1628
		svscmd_info_t reliableCommandInfo[128]; // 2652
		int reliableSequence; // 134748
		int reliableAcknowledge; // 134752
		int reliableSent; // 134756
		int messageAcknowledge; // 134760
		int gamestateMessageNum; // 134764
		int challenge; // 134768
		usercmd_s lastUsercmd; // 134772
		int lastClientCommand; // 134812
		char lastClientCommandString[1024]; // 134816
		gentity_s* gentity; // 135840
		char name[16]; // 135844
		int nextReliableTime; // 135860
		int lastPacketTime; // 135864
		int lastConnectTime; // 135868
		int nextSnapshotTime; // 135872
		int timeoutCount; // 135876
		int ping; // 135880
		int rate;
		int snapshotMsec;
		int snapshotBackoffCount;
		int pureAuthentic; // 135896
		char netchanOutgoingBuffer[131072];
		char netchanIncomingBuffer[2048];
		char playerGuid[17];
		unsigned short scriptId; // 269038
		int bIsTestClient; // 269040
		int serverID; // 269044
		bool usingOnlineStatsOffline;
		struct
		{
			unsigned int checksum;
			struct
			{
				unsigned char binary[2000];
				int data[1547];
			} __s0;
		} stats;
		char statsModifiedFlags[1024];
		bool statsModified;
		char statPacketsReceived;
		bool steamAuthorized;
		char steamAuthFailCount;
		unsigned __int64 steamID; // 278272
		bool sendMatchData;
		int matchDataSendTime;
		clientSnapshot_t frames[32];
	};

	static_assert(sizeof(client_s) == 0xA6790);

	enum CompassType
	{
		COMPASS_TYPE_PARTIAL = 0x0,
		COMPASS_TYPE_FULL = 0x1,
	};

	struct clientConnection_t
	{
		int qport;
		int clientNum;
		int lastPacketSentTime;
		int lastPacketTime;
		netadr_t serverAddress;
		int connectTime;
		int connectPacketCount;
		char serverMessage[256];
		int challenge;
		int checksumFeed;
		int reliableSequence;
		int reliableAcknowledge;
		char reliableCommands[128][1024];
		int serverMessageSequence;
		int serverCommandSequence;
		int lastExecutedServerCommand;
		char serverCommands[128][1024];
		bool isServerRestarting;
		int lastClientArchiveIndex;
		char demoName[MAX_QPATH];
		int demorecording;
		int demoplaying;
		int isTimeDemo;
		int demowaiting;
		int(__cdecl* demoread)(void*, int, int);
		int demofile;
		int timeDemoLog;
		int timeDemoFrames;
		int timeDemoStart;
		int timeDemoPrev;
		int timeDemoBaseTime;
		netchan_t netchan;
		char netchanOutgoingBuffer[2048];
		char netchanIncomingBuffer[131072];
		netProfileInfo_t OOBProf;
		char statPacketsToSend;
		int statPacketSendTime[7];
	};

	static_assert(sizeof(clientConnection_t) == 0x615E8); // Size confirmed in CL_Migrate

	struct CModelAllocData
	{
		void* mainArray;
		void* vertexBuffer;
		void* indexBuffer;
	};

	struct CModelSectionHeader
	{
		int size;
		int offset;
		int fixupStart;
		int fixupCount;
		void* buffer;
	};

	enum CModelSection
	{
		SECTION_MAIN = 0,
		SECTION_INDEX = 1,
		SECTION_VERTEX = 2,
		SECTION_FIXUP = 3,
	};

	struct CModelHeader
	{
		int version;
		unsigned int signature;
		CModelSectionHeader sectionHeader[4];
	};

	struct punctuation_s
	{
		char* p; //punctuation character(s)
		int n; //punctuation indication
		punctuation_s* next; //next punctuation
	};

#define MAX_TOKEN 1024
#define MAX_TOKENLENGTH 1024

	enum parseSkip_t
	{
		SKIP_NO = 0x0,
		SKIP_YES = 0x1,
		SKIP_ALL_ELIFS = 0x2,
	};

	struct token_s
	{
		char string[MAX_TOKEN]; // available token
		int type; // last read token type
		int subtype; // last read token sub type
		unsigned long int intvalue; // integer value
		long double floatvalue; // floating point value
		char* whitespace_p; // start of white space before token
		char* endwhitespace_p; // start of white space before token
		int line; // line the token was on
		int linescrossed; // lines crossed in white space
		token_s* next; // next token in chain
	};

	struct script_s
	{
		char filename[64]; //file name of the script
		char* buffer; //buffer containing the script
		char* script_p; //current pointer in the script
		char* end_p; //pointer to the end of the script
		char* lastscript_p; //script pointer before reading token
		char* whitespace_p; //begin of the white space
		char* endwhitespace_p; //end of the white space
		int length; //length of the script in bytes
		int line; //current line in script
		int lastline; //line before reading token
		int tokenavailable; //set by UnreadLastToken
		int flags; //several script flags
		punctuation_s* punctuations; //the punctuations used in the script
		punctuation_s** punctuationtable;
		token_s token; //available token
		script_s* next; //next script in a chain
	};

	struct define_s
	{
		char* name; //define name
		int flags; //define flags
		int builtin; // > 0 if builtin define
		int numparms; //number of define parameters
		token_s* parms; //define parameters
		token_s* tokens; //macro tokens (possibly containing parm tokens)
		define_s* next; //next defined macro in a list
		define_s* hashnext; //next define in the hash chain
	};

	struct indent_s
	{
		int type; //indent type
		int skip; //true if skipping current indent
		script_s* script; //script the indent was in
		indent_s* next; //next indent on the indent stack
	};

	struct source_s
	{
		char filename[MAX_QPATH]; //file name of the script
		char includepath[MAX_QPATH]; //path to include files
		punctuation_s* punctuations; //punctuations to use
		script_s* scriptstack; //stack with scripts of the source
		token_s* tokens; //tokens to read first
		define_s* defines; //list with macro definitions
		define_s** definehash; //hash chain with defines
		indent_s* indentstack; //stack with indents
		int skip; // > 0 if skipping conditional code
		token_s token; //last read token
	};

	struct directive_s
	{
		const char* name;
		int (*func)(source_s* source);
	};

	struct pc_token_s
	{
		int type;
		int subtype;
		int intvalue;
		float floatvalue;
		char string[MAX_TOKENLENGTH];
	};

	template <typename T, int N, int M>
	struct KeywordHashEntry
	{
		const char* keyword;
		int (*func)(T*, int);
	};

	enum MaterialTechniqueType
	{
		TECHNIQUE_DEPTH_PREPASS = 0x0,
		TECHNIQUE_BUILD_FLOAT_Z = 0x1,
		TECHNIQUE_BUILD_SHADOWMAP_DEPTH = 0x2,
		TECHNIQUE_BUILD_SHADOWMAP_COLOR = 0x3,
		TECHNIQUE_UNLIT = 0x4,
		TECHNIQUE_EMISSIVE = 0x5,
		TECHNIQUE_EMISSIVE_DFOG = 0x6,
		TECHNIQUE_EMISSIVE_SHADOW = 0x7,
		TECHNIQUE_EMISSIVE_SHADOW_DFOG = 0x8,
		TECHNIQUE_LIT_BEGIN = 0x9,
		TECHNIQUE_LIT = 0x9,
		TECHNIQUE_LIT_DFOG = 0xA,
		TECHNIQUE_LIT_SUN = 0xB,
		TECHNIQUE_LIT_SUN_DFOG = 0xC,
		TECHNIQUE_LIT_SUN_SHADOW = 0xD,
		TECHNIQUE_LIT_SUN_SHADOW_DFOG = 0xE,
		TECHNIQUE_LIT_SPOT = 0xF,
		TECHNIQUE_LIT_SPOT_DFOG = 0x10,
		TECHNIQUE_LIT_SPOT_SHADOW = 0x11,
		TECHNIQUE_LIT_SPOT_SHADOW_DFOG = 0x12,
		TECHNIQUE_LIT_OMNI = 0x13,
		TECHNIQUE_LIT_OMNI_DFOG = 0x14,
		TECHNIQUE_LIT_OMNI_SHADOW = 0x15,
		TECHNIQUE_LIT_OMNI_SHADOW_DFOG = 0x16,
		TECHNIQUE_LIT_INSTANCED = 0x17,
		TECHNIQUE_LIT_INSTANCED_DFOG = 0x18,
		TECHNIQUE_LIT_INSTANCED_SUN = 0x19,
		TECHNIQUE_LIT_INSTANCED_SUN_DFOG = 0x1A,
		TECHNIQUE_LIT_INSTANCED_SUN_SHADOW = 0x1B,
		TECHNIQUE_LIT_INSTANCED_SUN_SHADOW_DFOG = 0x1C,
		TECHNIQUE_LIT_INSTANCED_SPOT = 0x1D,
		TECHNIQUE_LIT_INSTANCED_SPOT_DFOG = 0x1E,
		TECHNIQUE_LIT_INSTANCED_SPOT_SHADOW = 0x1F,
		TECHNIQUE_LIT_INSTANCED_SPOT_SHADOW_DFOG = 0x20,
		TECHNIQUE_LIT_INSTANCED_OMNI = 0x21,
		TECHNIQUE_LIT_INSTANCED_OMNI_DFOG = 0x22,
		TECHNIQUE_LIT_INSTANCED_OMNI_SHADOW = 0x23,
		TECHNIQUE_LIT_INSTANCED_OMNI_SHADOW_DFOG = 0x24,
		TECHNIQUE_LIT_END = 0x25,
		TECHNIQUE_LIGHT_SPOT = 0x25,
		TECHNIQUE_LIGHT_OMNI = 0x26,
		TECHNIQUE_LIGHT_SPOT_SHADOW = 0x27,
		TECHNIQUE_FAKELIGHT_NORMAL = 0x28,
		TECHNIQUE_FAKELIGHT_VIEW = 0x29,
		TECHNIQUE_SUNLIGHT_PREVIEW = 0x2A,
		TECHNIQUE_CASE_TEXTURE = 0x2B,
		TECHNIQUE_WIREFRAME_SOLID = 0x2C,
		TECHNIQUE_WIREFRAME_SHADED = 0x2D,
		TECHNIQUE_DEBUG_BUMPMAP = 0x2E,
		TECHNIQUE_DEBUG_BUMPMAP_INSTANCED = 0x2F,
		TECHNIQUE_COUNT = 0x30,
		TECHNIQUE_TOTAL_COUNT = 0x31,
		TECHNIQUE_NONE = 0x32,
	};

	enum MaterialVertexDeclType
	{
		VERTDECL_GENERIC = 0x0,
		VERTDECL_PACKED = 0x1,
		VERTDECL_WORLD = 0x2,
		VERTDECL_WORLD_T1N0 = 0x3,
		VERTDECL_WORLD_T1N1 = 0x4,
		VERTDECL_WORLD_T2N0 = 0x5,
		VERTDECL_WORLD_T2N1 = 0x6,
		VERTDECL_WORLD_T2N2 = 0x7,
		VERTDECL_WORLD_T3N0 = 0x8,
		VERTDECL_WORLD_T3N1 = 0x9,
		VERTDECL_WORLD_T3N2 = 0xA,
		VERTDECL_WORLD_T4N0 = 0xB,
		VERTDECL_WORLD_T4N1 = 0xC,
		VERTDECL_WORLD_T4N2 = 0xD,
		VERTDECL_POS_TEX = 0xE,
		VERTDECL_STATICMODELCACHE = 0xF,
		VERTDECL_COUNT = 0x10,
	};

	struct $A6DFE8F2BEFD3E7315B44D22E582538B
	{
		unsigned int stride;
		IDirect3DVertexBuffer9* vb;
		unsigned int offset;
	};

	struct GfxCmdBufPrimState
	{
		IDirect3DDevice9* device;
		IDirect3DIndexBuffer9* indexBuffer;
		MaterialVertexDeclType vertDeclType;
		$A6DFE8F2BEFD3E7315B44D22E582538B streams[2];
		IDirect3DVertexDeclaration9* vertexDecl;
	};

	enum GfxDepthRangeType
	{
		GFX_DEPTH_RANGE_SCENE = 0x0,
		GFX_DEPTH_RANGE_VIEWMODEL = 0x2,
		GFX_DEPTH_RANGE_FULL = 0xFFFFFFFF,
	};

	struct GfxViewport
	{
		int x;
		int y;
		int width;
		int height;
	};

	enum GfxRenderTargetId
	{
		R_RENDERTARGET_SAVED_SCREEN = 0x0,
		R_RENDERTARGET_FRAME_BUFFER = 0x1,
		R_RENDERTARGET_SCENE = 0x2,
		R_RENDERTARGET_RESOLVED_POST_SUN = 0x3,
		R_RENDERTARGET_RESOLVED_SCENE = 0x4,
		R_RENDERTARGET_FLOAT_Z = 0x5,
		R_RENDERTARGET_PINGPONG_0 = 0x6,
		R_RENDERTARGET_PINGPONG_1 = 0x7,
		R_RENDERTARGET_POST_EFFECT_0 = 0x8,
		R_RENDERTARGET_POST_EFFECT_1 = 0x9,
		R_RENDERTARGET_SHADOWMAP_LARGE = 0xA,
		R_RENDERTARGET_SHADOWMAP_SMALL = 0xB,
		R_RENDERTARGET_COUNT = 0xC,
		R_RENDERTARGET_NONE = 0xD,
	};

	struct GfxDrawPrimArgs
	{
		int vertexCount;
		int triCount;
		int baseIndex;
	};

	struct GfxCmdBufState
	{
		char refSamplerState[16];
		unsigned int samplerState[16];
		GfxTexture* samplerTexture[16];
		GfxCmdBufPrimState prim;
		Material* material;
		MaterialTechniqueType techType;
		MaterialTechnique* technique;
		MaterialPass* pass;
		unsigned int passIndex;
		GfxDepthRangeType depthRangeType;
		float depthRangeNear;
		float depthRangeFar;
		unsigned __int64 vertexShaderConstState[64];
		unsigned __int64 pixelShaderConstState[256];
		char alphaRef;
		unsigned int refStateBits[2];
		unsigned int activeStateBits[2];
		MaterialPixelShader* pixelShader;
		MaterialVertexShader* vertexShader;
		unsigned int scissorX;
		unsigned int scissorY;
		unsigned int scissorW;
		unsigned int scissorH;
		unsigned int pixPrimarySortKey;
		unsigned int pixSceneLightIndex;
		Material* pixMaterial;
		MaterialTechnique* pixTechnique;
		int pixCombine;
		GfxViewport viewport;
		GfxRenderTargetId renderTargetId;
		Material* origMaterial;
		MaterialTechniqueType origTechType;
	};

	enum MaterialTextureSource : unsigned int
	{
		TEXTURE_SRC_CODE_BLACK = 0x0,
		TEXTURE_SRC_CODE_WHITE = 0x1,
		TEXTURE_SRC_CODE_IDENTITY_NORMAL_MAP = 0x2,
		TEXTURE_SRC_CODE_MODEL_LIGHTING = 0x3,
		TEXTURE_SRC_CODE_LIGHTMAP_PRIMARY = 0x4,
		TEXTURE_SRC_CODE_LIGHTMAP_SECONDARY = 0x5,
		TEXTURE_SRC_CODE_SHADOWMAP_SUN = 0x6,
		TEXTURE_SRC_CODE_SHADOWMAP_SPOT = 0x7,
		TEXTURE_SRC_CODE_FEEDBACK = 0x8,
		TEXTURE_SRC_CODE_RESOLVED_POST_SUN = 0x9,
		TEXTURE_SRC_CODE_RESOLVED_SCENE = 0xA,
		TEXTURE_SRC_CODE_POST_EFFECT_0 = 0xB,
		TEXTURE_SRC_CODE_POST_EFFECT_1 = 0xC,
		TEXTURE_SRC_CODE_LIGHT_ATTENUATION = 0xD,
		TEXTURE_SRC_CODE_OUTDOOR = 0xE,
		TEXTURE_SRC_CODE_FLOATZ = 0xF,
		TEXTURE_SRC_CODE_PROCESSED_FLOATZ = 0x10,
		TEXTURE_SRC_CODE_RAW_FLOATZ = 0x11,
		TEXTURE_SRC_CODE_HALF_PARTICLES = 0x12,
		TEXTURE_SRC_CODE_HALF_PARTICLES_Z = 0x13,
		TEXTURE_SRC_CODE_CASE_TEXTURE = 0x14,
		TEXTURE_SRC_CODE_CINEMATIC_Y = 0x15,
		TEXTURE_SRC_CODE_CINEMATIC_CR = 0x16,
		TEXTURE_SRC_CODE_CINEMATIC_CB = 0x17,
		TEXTURE_SRC_CODE_CINEMATIC_A = 0x18,
		TEXTURE_SRC_CODE_REFLECTION_PROBE = 0x19,
		TEXTURE_SRC_CODE_ALTERNATE_SCENE = 0x1A,
		TEXTURE_SRC_CODE_COUNT = 0x1B,
	};

	struct GfxCmdBufSourceState;

	struct GfxCmdBufContext
	{
		GfxCmdBufSourceState* source;
		GfxCmdBufState* state;
	};

	struct GfxDrawGroupSetupFields
	{
		unsigned __int16 materialSortedIndex : 15;
		unsigned __int16 useHeroLighting : 1;
		char sceneLightIndex;
		char surfType;
	};

	union GfxDrawGroupSetup
	{
		GfxDrawGroupSetupFields fields;
		unsigned int packed;
	};

	struct GfxMarkSurfLightingFields
	{
		char lmapIndex;
		char reflectionProbeIndex;
		unsigned __int16 modelIndex;
	};

	union GfxMarkSurfLighting
	{
		GfxMarkSurfLightingFields fields;
		unsigned int packed;
	};

	struct GfxMarkSurf
	{
		GfxDrawGroupSetup drawGroup;
		unsigned __int16* indices;
		unsigned __int16 triCount;
		char modelType;
		char pad;
		GfxMarkSurfLighting lighting;
	};

	struct GfxCodeSurf
	{
		GfxDrawGroupSetup drawGroup;
		unsigned int triCount;
		unsigned __int16* indices;
		unsigned __int16 argOffset;
		unsigned __int16 argCount;
	};

	struct __declspec(align(4)) GfxGlassSurf
	{
		GfxDrawGroupSetup drawGroup;
		char pad;
		char reflectionProbeIndex;
		unsigned __int16 triCount;
		unsigned __int16* indices;
		unsigned __int16 lightingHandle;
	};

	struct GfxCloudSurfFields
	{
		unsigned __int16 materialSortedIndex;
		char cloudDataIndex;
		char surfType;
	};

	union GfxCloudSurf
	{
		GfxCloudSurfFields fields;
		unsigned int packed;
	};

	struct GfxSparkSurfFields
	{
		unsigned __int16 materialSortedIndex;
		unsigned __int16 sparkDataIndex;
	};

	union GfxSparkSurf
	{
		GfxSparkSurfFields fields;
		unsigned int packed;
	};

	struct GfxSceneDef
	{
		int time;
		float floatTime;
		float viewOffset[3];
		GfxImage* sunShadowImage;
		float sunShadowPixelAdjust[4];
	};

	struct GfxMatrix
	{
		float m[4][4];
	};

	struct GfxCodeMatrices
	{
		GfxMatrix matrix[56];
	};

	struct GfxCamera
	{
		float origin[3];
		float axis[3][3];
		float subWindowMins[2];
		float subWindowMaxs[2];
		float tanHalfFovX;
		float tanHalfFovY;
		float zNear;
		float depthHackNearClip;
	};

	struct GfxViewParms
	{
		GfxMatrix viewMatrix;
		GfxMatrix projectionMatrix;
		GfxMatrix viewProjectionMatrix;
		GfxMatrix inverseViewProjectionMatrix;
		GfxCamera camera;
	};

	struct GfxBackEndData;
	struct GfxCmdBufInput
	{
		float consts[76][4];
		GfxImage* codeImages[27];
		char codeImageSamplerStates[27];
		GfxBackEndData* data;
	};


	enum GfxViewMode
	{
		VIEW_MODE_NONE = 0x0,
		VIEW_MODE_3D = 0x1,
		VIEW_MODE_2D = 0x2,
		VIEW_MODE_IDENTITY = 0x3,
	};

	enum GfxViewportBehavior
	{
		GFX_USE_VIEWPORT_FOR_VIEW = 0x0,
		GFX_USE_VIEWPORT_FULL = 0x1,
	};

	enum ShadowType
	{
		SHADOW_NONE = 0x0,
		SHADOW_MAP = 0x1,
	};

	struct GfxDepthOfField
	{
		float viewModelStart;
		float viewModelEnd;
		float nearStart;
		float nearEnd;
		float farStart;
		float farEnd;
		float nearBlur;
		float farBlur;
	};

	struct GfxFilm
	{
		bool enabled;
		float brightness;
		float contrast;
		float desaturation;
		float desaturationDark;
		bool invert;
		float tintDark[3];
		float tintMedium[3];
		float tintLight[3];
	};

	struct GfxGlow
	{
		bool enabled;
		float bloomCutoff;
		float bloomDesaturation;
		float bloomIntensity;
		float radius;
	};

	struct GfxLightScale
	{
		float diffuseScale;
		float specularScale;
	};

	struct GfxStageInfo
	{
		Stage activeStage;
		bool activeStageValid;
	};

	struct GfxCompositeFx
	{
		GfxFilm film;
		float distortionScale[3];
		float blurRadius;
		float distortionMagnitude;
		float frameRate;
		int lastUpdate;
		int frame;
		int startMSec;
		int currentTime;
		int duration;
		bool enabled;
		bool scriptEnabled;
	};

	struct GfxVertexBufferState
	{
		volatile int used;
		int total;
		IDirect3DVertexBuffer9* buffer;
		char* verts;
	};

	struct GfxMeshData
	{
		unsigned int indexCount;
		unsigned int totalIndexCount;
		unsigned __int16* indices;
		GfxVertexBufferState vb;
		unsigned int vertSize;
	};

	struct GfxQuadMeshData
	{
		float x;
		float y;
		float width;
		float height;
		GfxMeshData meshData;
	};

	struct GfxSparkSurfList
	{
		GfxSparkSurf* surfs;
		unsigned int count;
	};

	enum GfxCodeSurfListType
	{
		GFX_CODE_SURFLIST_INVALID = -1,
		GFX_CODE_SURFLIST_TRANS = 0x0,
		GFX_CODE_SURFLIST_EMISSIVE = 0x1,
		GFX_CODE_SURFLIST_TYPE_COUNT = 0x2,
	};


	struct GfxViewInfo;

	struct GfxDrawListInfo
	{
		MaterialTechniqueType baseTechType;
		GfxViewInfo* viewInfo;
		float eyeOffset[3];
		unsigned int sceneLightIndex;
		int cameraView;
		GfxCodeSurfListType codeSurfListType;
	};

	struct GfxBspSurfList
	{
		unsigned int count;
		const unsigned __int16* stream;
	};

	struct GfxSModelSurfList
	{
		unsigned int surfDataBytes;
		const char* surfData;
		const char* visData;
	};

	struct GfxDrawSurfList
	{
		GfxDrawSurf* array;
		unsigned int count;
	};

	struct GfxPreTessSurf
	{
		GfxDrawGroupSetup drawGroup;
		char lightmapIndex;
		char reflectionProbeIndex;
		unsigned __int16 triCount;
		unsigned int baseIndex;
		unsigned int firstVertex;
		IDirect3DVertexBuffer9* vb;
		unsigned int vertexCount;
	};

	struct GfxPreTessSurfList
	{
		GfxPreTessSurf* surfs;
		unsigned int count;
	};

	struct GfxCodeSurfList
	{
		GfxCodeSurf* surfs;
		unsigned int count;
	};

	struct GfxMarkSurfList
	{
		GfxMarkSurf* surfs;
		unsigned int count;
	};

	struct GfxGlassSurfList
	{
		GfxGlassSurf* surfs;
		unsigned int count;
	};

	struct GfxScaledPlacement
	{
		GfxPlacement base;
		float scale;
	};

	struct GfxParticleCloud
	{
		GfxScaledPlacement placement;
		float endpos[3];
		GfxColor color;
		float radius[2];
		unsigned int flags;
		float timeOffset;
	};

	struct GfxCloudSurfList
	{
		GfxParticleCloud* particles;
		GfxCloudSurf* surfs;
		unsigned int count;
	};

	struct GfxDrawList
	{
		GfxBspSurfList bspSurfList;
		GfxPreTessSurfList bspPreTessSurfList;
		GfxSModelSurfList smodelSurfList[4];
		GfxDrawSurfList drawSurfList;
		GfxCodeSurfList codeSurfList;
		GfxMarkSurfList markSurfList;
		GfxGlassSurfList glassSurfList;
		GfxCloudSurfList cloudSurfList;
		GfxSparkSurfList sparkSurfList;
		GfxDrawListInfo info;
	};

	struct GfxViewInfo
	{
		GfxViewParms viewParms;
		GfxViewport sceneViewport;
		GfxViewport displayViewport;
		GfxViewport scissorViewport;
		GfxSceneDef sceneDef;
		ShadowType dynamicShadowType;
		char floatZUsage;
		bool needsDistortionResolve;
		bool viewModelHasDistortion;
		char forceSunShadowsGenerate;
		unsigned int sceneLightCount;
		float blurRadius;
		float frustumPlanes[4][4];
		GfxDepthOfField dof;
		GfxFilm film;
		GfxGlow glow;
		GfxLightScale charPrimaryLightScale;
		GfxStageInfo stageInfo;
		GfxCompositeFx waterSheetingFx;
		const void* displayCmds;
		GfxQuadMeshData* fullSceneViewMesh;
		GfxDrawList drawList[10];
		//__declspec(align(16)) GfxCmdBufInput input;
		GfxRenderTargetId renderTargetId;
		bool useShadows;
		unsigned int sunShadowResolution;
		GfxRenderTargetId sunShadowRenderTargetId;
		unsigned int sunShadowTileCount;
	};

	struct GfxLight
	{
		char type;
		char canUseShadowMap;
		char unused[2];
		float color[3];
		float dir[3];
		float origin[3];
		float radius;
		float cosHalfFovOuter;
		float cosHalfFovInner;
		int exponent;
		unsigned int spotShadowIndex;
		GfxLightDef* def;
	};

	struct GfxVisibleLight
	{
		char pad[0x2004];
	};

	struct GfxEntity
	{
		unsigned int renderFxFlags;
		float materialTime;
	};

	struct GfxSkinnedXModelSurfs
	{
		void* firstSurf;
	};

	struct GfxSceneEntityCull
	{
		volatile unsigned int state;
		Bounds bounds;
		GfxSkinnedXModelSurfs skinnedSurfs;
	};

	union GfxSceneEntityInfo
	{
		void/*cpose_t*/* pose;
		unsigned __int16* cachedLightingHandle;
	};

	struct DSkelPartBits
	{
		int anim[6];
		int control[6];
		int worldCtrl[6];
		int skel[6];
	};

	struct DSkel
	{
		DSkelPartBits partBits;
		int timeStamp;
		DObjAnimMat* mat;
	};

	struct bitarray
	{
		int array[6];
	};

	/* 1923 */
	struct XAnimCalcAnimInfo
	{
		DObjAnimMat rotTransArray[1152];
		bitarray animPartBits;
		bitarray ignorePartBits;
	};


	struct DObj
	{
		/*XAnimTree_s*/ void* tree;
		unsigned __int16 duplicateParts;
		unsigned __int16 entnum;
		char duplicatePartsSize;
		char numModels;
		char numBones;
		char flags;
		unsigned int ignoreCollision;
		volatile int locked;
		DSkel skel;
		float radius;
		unsigned int hidePartBits[6];
		XModel** models;
	};

	struct GfxSceneEntity
	{
		float lightingOrigin[3];
		GfxPlacement placement;
		GfxSceneEntityCull cull;
		char lods[32];
		unsigned __int32 gfxEntIndex : 7;
		unsigned __int32 entnum : 12;
		unsigned __int32 renderFxFlags : 13;
		DObj* obj;
		GfxSceneEntityInfo info;
		char reflectionProbeIndex;
	};

	struct GfxCmdBufSourceState
	{
		GfxCodeMatrices matrices;
		GfxCmdBufInput input;
		GfxViewParms viewParms;
		float eyeOffset[4];
		GfxMatrix shadowLookupMatrix;
		unsigned __int16 constVersions[132];
		unsigned __int16 matrixVersions[14];
		unsigned int sceneLightForShadowLookupMatrix;
		GfxPlacement* objectPlacement[3];
		GfxViewParms* viewParms3D;
		unsigned int depthHackFlags;
		GfxScaledPlacement skinnedPlacement;
		int cameraView;
		GfxViewMode viewMode;
		GfxSceneDef sceneDef;
		GfxViewport sceneViewport;
		float materialTime;
		GfxViewportBehavior viewportBehavior;
		int renderTargetWidth;
		int renderTargetHeight;
		bool viewportIsDirty;
		unsigned int sceneLightIndex;
		bool useHeroLighting;
	};

	struct GfxSceneModel
	{
		XModelDrawInfo info;
		XModel* model;
		DObj* obj;
		GfxScaledPlacement placement;
		unsigned __int32 gfxEntIndex : 7;
		unsigned __int32 entnum : 12;
		unsigned __int32 renderFxFlags : 13;
		float radius;
		unsigned __int16* cachedLightingHandle;
		float lightingOrigin[3];
		char reflectionProbeIndex;
		char lod;
	};

	struct __declspec(align(4)) GfxSceneBrush
	{
		BModelDrawInfo info;
		unsigned __int16 entnum;
		GfxBrushModel* bmodel;
		GfxPlacement placement;
		char reflectionProbeIndex;
	};

	union GfxSceneGlass
	{
		struct
		{
			bool rendered;
			char reflectionProbeIndex;
			unsigned __int16 lightingHandle;
		};
		unsigned int packed;
	};

	union GfxEntCellRefInfo
	{
		float radius;
		GfxBrushModel* bmodel;
	};

	struct GfxSceneDpvs
	{
		unsigned int localClientNum;
		char* entVisData[7];
		unsigned __int16* sceneXModelIndex;
		unsigned __int16* sceneDObjIndex;
		GfxEntCellRefInfo* entInfo[4];
	};

	struct __declspec(align(64)) GfxScene
	{
		GfxCodeSurf codeEmissiveSurfs[2048];
		GfxCodeSurf codeTransSurfs[640];
		GfxMarkSurf markSurfs[1536];
		GfxGlassSurf glassSurfs[768];
		GfxCloudSurf cloudSurfs[256];
		GfxDrawSurf drawSurfsDepthHack[32];
		GfxDrawSurf drawSurfsLitOpaque[8192];
		GfxDrawSurf drawSurfsLitTrans[2048];
		GfxDrawSurf drawSurfsEmissive[8192];
		GfxDrawSurf drawSurfsSunShadow0[4096];
		GfxDrawSurf drawSurfsSunShadow1[8192];
		GfxDrawSurf drawSurfsSpotShadow0[896];
		GfxDrawSurf drawSurfsSpotShadow1[896];
		GfxDrawSurf drawSurfsSpotShadow2[896];
		GfxDrawSurf drawSurfsSpotShadow3[896];
		unsigned int sceneLightIsUsed[32];
		unsigned int cachedSceneLightIsUsed[4][32];
		GfxSparkSurf sparkSurfs[64];
		unsigned int drawSurfLimit[10];
		volatile int drawSurfCount[10];
		GfxDrawSurf* drawSurfs[10];
		volatile int codeSurfUser[2];
		volatile int markMeshGuard;
		unsigned int codeEmissiveSurfCount;
		unsigned int codeTransSurfCount;
		unsigned int markSurfCount;
		unsigned int glassSurfCount;
		GfxSceneDef def;
		unsigned int addedLightCount;
		GfxLight addedLight[32];
		bool isAddedLightCulled[32];
		float dynamicSpotLightNearPlaneOffset;
		float dynamicSpotLightLength;
		GfxVisibleLight visLight[4];
		GfxVisibleLight visLightShadow[1];
		unsigned int* entOverflowedDrawBuf;
		volatile int gfxEntCount;
		GfxEntity gfxEnts[128];
		int sceneDObjCount;
		int preClientSceneDObjCount;
		int sceneDObjCountAtMark;
		GfxSceneEntity sceneDObj[520];
		char sceneDObjVisData[7][512];
		int sceneDObjMarkableViewmodelIndex;
		unsigned int sceneDObjFirstViewmodelIndex;
		unsigned int sceneDObjViewmodelCount;
		volatile int sceneModelCount;
		int sceneModelCountAtMark;
		int sceneDObjModelCount;
		GfxSceneModel sceneModel[1024];
		char sceneModelVisData[7][1024];
		volatile int sceneBrushCount;
		int sceneBrushCountAtMark;
		GfxSceneBrush sceneBrush[512];
		char sceneBrushVisData[3][512];
		GfxSceneGlass sceneGlass[1024];
		unsigned int sceneDynModelCount;
		unsigned int sceneDynBrushCount;
		int gfxEntCountAtMark;
		GfxSceneDpvs dpvs;
		int updateSound;
		int allowAddDObj;
	};

	enum TextRenderFlags
	{
		TEXT_RENDERFLAG_FORCEMONOSPACE = 0x1,
		TEXT_RENDERFLAG_CURSOR = 0x2,
		TEXT_RENDERFLAG_DROPSHADOW = 0x4,
		TEXT_RENDERFLAG_DROPSHADOW_EXTRA = 0x8,
		TEXT_RENDERFLAG_GLOW = 0x10,
		TEXT_RENDERFLAG_GLOW_FORCE_COLOR = 0x20,
		TEXT_RENDERFLAG_FX_DECODE = 0x40,
		TEXT_RENDERFLAG_PADDING = 0x80,
		TEXT_RENDERFLAG_SUBTITLETEXT = 0x100,
		TEXT_RENDERFLAG_CINEMATIC = 0x200,
		TEXT_RENDERFLAG_OUTLINE = 0x400,
		TEXT_RENDERFLAG_OUTLINE_EXTRA = 0x800,
	};

	enum FontPassType
	{
		FONTPASS_NORMAL = 0x0,
		FONTPASS_GLOW = 0x1,
		FONTPASS_OUTLINE = 0x2,
		FONTPASS_COUNT = 0x3,
	};

	struct AimInput
	{
		float deltaTime;
		float deltaTimeScaled;
		float pitch;
		float pitchAxis;
		float pitchMax;
		float yaw;
		float yawAxis;
		float yawMax;
		float forwardAxis;
		float rightAxis;
		int buttons;
		int localClientNum;
	};

	struct AimOutput
	{
		float pitch;
		float yaw;
		float meleeChargeYaw;
		char meleeChargeDist;
	};

	struct clientLogo_t
	{
		int startTime;
		int duration;
		int fadein;
		int fadeout;
		Material* material[2];
	};

	struct vidConfig_t
	{
		unsigned int sceneWidth;
		unsigned int sceneHeight;
		unsigned int displayWidth;
		unsigned int displayHeight;
		unsigned int displayFrequency;
		int isFullscreen;
		float aspectRatioWindow;
		float aspectRatioScenePixel;
		float aspectRatioDisplayPixel;
		unsigned int maxTextureSize;
		unsigned int maxTextureMaps;
		bool deviceSupportsGamma;
	};

	struct trDebugLine_t
	{
		float start[3];
		float end[3];
		float color[4];
		int depthTest;
	};

	struct trDebugString_t
	{
		float xyz[3];
		float color[4];
		float scale;
		char text[96];
	};

	struct clientDebugStringInfo_t
	{
		int max;
		int num;
		trDebugString_t* strings;
		int* durations;
	};

	struct clientDebugLineInfo_t
	{
		int max;
		int num;
		trDebugLine_t* lines;
		int* durations;
	};

	struct clientDebug_t
	{
		int prevFromServer;
		int fromServer;
		clientDebugStringInfo_t clStrings;
		clientDebugStringInfo_t svStringsBuffer;
		clientDebugStringInfo_t svStrings;
		clientDebugLineInfo_t clLines;
		clientDebugLineInfo_t svLinesBuffer;
		clientDebugLineInfo_t svLines;
	};

	struct ClientMatchData
	{
		char def[64];
		char data[1024];
	};

	struct clientStatic_t
	{
		int quit;
		int hunkUsersStarted;
		char servername[256];
		int rendererStarted;
		int soundStarted;
		int uiStarted;
		int frametime;
		float frametime_base;
		int realtime;
		bool gpuSyncedPrevFrame;
		bool inputUpdatedPrevFrame;
		clientLogo_t logo;
		float mapCenter[3];
		int lastServerPinged;
		int pingedServerCount;
		int totalServersParsed;
		int pingUpdateSource;
		Material* whiteMaterial;
		Material* consoleMaterial;
		Font_s* consoleFont;
		vidConfig_t vidConfig;
		clientDebug_t debug;
		int doVidRestart;
		ClientMatchData matchData;
		XNADDR xnaddrs[18];
		float debugRenderPos[3];
		int skelValid;
		int skelTimeStamp;
		volatile int skelMemPos;
		char skelMemory[262144];
		char* skelMemoryStart;
		bool allowedAllocSkel;
		int serverId;
		gameState_t cl_gameState;
		clSnapshot_t noDeltaSnapshot;
		int nextNoDeltaEntity;
		entityState_s noDeltaEntities[1024];
	};

	static_assert(sizeof(clientStatic_t) == 0xA7AEC);

	struct ConDrawInputGlob
	{
		char autoCompleteChoice[64];
		int matchIndex;
		int matchCount;
		const char* inputText;
		int inputTextLen;
		bool hasExactMatch;
		bool mayAutoComplete;
		float x;
		float y;
		float leftX;
		float fontHeight;
	};

	struct ScreenPlacement
	{
		float scaleVirtualToReal[2];
		float scaleVirtualToFull[2];
		float scaleRealToVirtual[2];
		float realViewportPosition[2];
		float realViewportSize[2];
		float virtualViewableMin[2];
		float virtualViewableMax[2];
		float realViewableMin[2];
		float realViewableMax[2];
		float virtualAdjustableMin[2];
		float virtualAdjustableMax[2];
		float realAdjustableMin[2];
		float realAdjustableMax[2];
		float subScreenLeft;
	};

	struct serverStatusInfo_t
	{
		char address[64];
		const char* lines[128][4];
		char text[1024];
		char pings[54];
		int numLines;
	};

	struct pendingServer_t
	{
		char adrstr[64];
		char name[64];
		int startTime;
		int serverNum;
		int valid;
	};

	struct pendingServerStatus_t
	{
		int num;
		pendingServer_t server[16];
	};

	struct pinglist_t
	{
		char adrstr[64];
		int start;
	};

	struct serverStatus_s
	{
		pinglist_t pingList[16];
		int numqueriedservers;
		int currentping;
		int nextpingtime;
		int maxservers;
		int refreshtime;
		int numServers;
		int sortKey;
		int sortDir;
		int lastCount;
		int refreshActive;
		int currentServer;
		int displayServers[20000];
		int numDisplayServers;
		int serverCount;
		int numPlayersOnServers;
		int nextDisplayRefresh;
		int nextSortTime;
		int motdLen;
		int motdWidth;
		int motdPaintX;
		int motdPaintX2;
		int motdOffset;
		int motdTime;
		char motd[1024];
	};

	struct mapInfo
	{
		char mapName[32];
		char mapLoadName[16];
		char mapDescription[32];
		char mapLoadImage[32];
		char mapCustomKey[32][16];
		char mapCustomValue[32][64];
		int mapCustomCount;
		int teamMembers;
		int typeBits;
		int timeToBeat[32];
		int active;
	};

	struct gameTypeInfo
	{
		char gameType[12];
		char gameTypeName[32];
	};

	struct CachedAssets_t
	{
		Material* scrollBarArrowUp;
		Material* scrollBarArrowDown;
		Material* scrollBarArrowLeft;
		Material* scrollBarArrowRight;
		Material* scrollBar;
		Material* scrollBarThumb;
		Material* sliderBar;
		Material* sliderThumb;
		Material* whiteMaterial;
		Material* cursor;
		Material* textDecodeCharacters;
		Material* textDecodeCharactersGlow;
		Font_s* bigFont;
		Font_s* smallFont;
		Font_s* consoleFont;
		Font_s* boldFont;
		Font_s* textFont;
		Font_s* extraBigFont;
		Font_s* objectiveFont;
		Font_s* hudBigFont;
		Font_s* hudSmallFont;
		snd_alias_list_t* itemFocusSound;
	};

	struct sharedUiInfo_t
	{
		CachedAssets_t assets;
		int playerCount;
		char playerNames[18][32];
		char teamNames[18][32];
		int playerClientNums[18];
		volatile int updateGameTypeList;
		int numGameTypes;
		gameTypeInfo gameTypes[32];
		int numCustomGameTypes;
		gameTypeInfo customGameTypes[32];
		char customGameTypeCancelState[2048];
		int numJoinGameTypes;
		gameTypeInfo joinGameTypes[32];
		volatile int updateArenas;
		int mapCount;
		mapInfo mapList[128];
		int mapIndexSorted[128];
		bool mapsAreSorted;
		Material* serverHardwareIconList[9];
		unsigned __int64 partyMemberXuid;
		Material* talkingIcons[2];
		serverStatus_s serverStatus;
		char serverStatusAddress[64];
		serverStatusInfo_t serverStatusInfo;
		int nextServerStatusRefresh;
		pendingServerStatus_t pendingServerStatus;
	};

	struct GraphFloat
	{
		char name[64];
		float knots[32][2];
		unsigned __int16 knotCount;
		float scale;
	};

	struct XAnimTree_s
	{
		XAnim_s* anims;
		int info_usage;
		volatile int calcRefCount;
		volatile int modifyRefCount;
		unsigned __int16 children;
	};

	struct FxEffect
	{
		const FxEffectDef* def;
		volatile int status;
		unsigned __int16 firstElemHandle[3];
		unsigned __int16 firstSortedElemHandle;
		unsigned __int16 firstTrailHandle;
		unsigned __int16 firstSparkFountainHandle;
		unsigned __int16 pad16[1];
		unsigned __int16 randomSeed;
		unsigned __int16 owner;
		unsigned __int8 lighting[3];
		unsigned __int8 pad8[2];
		unsigned __int8 markViewmodelClientIndex;
		unsigned __int16 markEntnum;
		unsigned __int16 flags;
		unsigned __int8 bolt;
		unsigned __int8 runnerSortOrder;
		volatile int frameCount;
		int msecBegin;
		int msecLastUpdate;
		FxSpatialFrame frameAtSpawn;
		FxSpatialFrame frameNow;
		FxSpatialFrame framePrev;
		float distanceTravelled;
		char pad2[4];
	};

	static_assert(sizeof(FxEffect) == 0x90);

	struct CEntVehicleInfo
	{
		__int16 pitch;
		__int16 yaw;
		__int16 roll;
		__int16 barrelPitch;
		float barrelRoll;
		__int16 steerYaw;
		float time;
		unsigned __int16 wheelFraction[6];
		unsigned __int8 wheelBoneIndex[6];
		unsigned __int8 wheelSurfaceType[6];
		unsigned __int8 tag_body;
		unsigned __int8 tag_turret;
		unsigned __int8 tag_barrel;
	};

	static_assert(sizeof(CEntVehicleInfo) == 0x30);

	struct CEntFx
	{
		int triggerTime;
		FxEffect* effect;
	};

	struct CEntTurretAngles
	{
		float pitch;
		float yaw;
	};

	union $062DBEF1E2477FBB6A8D36FDF573DC79
	{
		CEntTurretAngles angles;
		const float* viewAngles;
	};

	struct CEntTurretInfo
	{
		$062DBEF1E2477FBB6A8D36FDF573DC79 ___u0;
		float barrelPitch;
		bool playerUsing;
		unsigned __int8 tagIdx_aim;
		unsigned __int8 tagIdx_aim_animated;
		unsigned __int8 tagIdx_aim_pivot;
		unsigned __int8 tagIdx_flash;
		unsigned __int8 tagIdx_barrel;
		float barrelRoll;
		bool barrelRollSndLastRotating;
		bool barrelRollSndNotified;
		int barrelRollSndTime;
		unsigned __int8 barrelRollSndIndex;
		bool wasOverheat;
	};

	static_assert(sizeof(CEntTurretInfo) == 0x24);

	struct clientControllers_t
	{
		float angles[4][3];
		float tag_origin_angles[3];
		float tag_origin_offset[3];
	};

	struct CEntPlayerInfo
	{
		clientControllers_t* control;
		unsigned __int8 tag[4];
	};

	static_assert(sizeof(CEntPlayerInfo) == 0x8);

	union $79C409BC84BCEABA56F6D25E37F2711D
	{
		CEntPlayerInfo player;
		CEntTurretInfo turret;
		CEntVehicleInfo vehicle;
		CEntFx fx;
	};

	struct GfxSkinCacheEntry
	{
		unsigned int frameCount;
		int skinnedCachedOffset;
		unsigned __int16 numSkinnedVerts;
		unsigned __int16 ageCount;
	};

	struct cpose_t
	{
		unsigned __int16 lightingHandle;
		unsigned __int8 eType;
		unsigned __int8 cullIn;
		unsigned int usedInScene;
		unsigned __int8 isRagdoll;
		int ragdollHandle;
		int killcamRagdollHandle;
		int physObjId;
		float origin[3];
		float angles[3];
		Game::GfxSkinCacheEntry skinCacheEntry;
		$79C409BC84BCEABA56F6D25E37F2711D ___u10;
	};

	static_assert(sizeof(cpose_t) == 0x6C); // Why was this 0x60? This is not Xbox! On computer, we have a model cache, so this is 6C

	struct centity_s
	{
		cpose_t pose;
		LerpEntityState prevState;
		entityState_s nextState;
		char nextValid;
		char bMuzzleFlash;
		char bTrailMade;
		char pad;
		unsigned __int8 tracerDrawRateCounter;
		unsigned __int8 weaponVisTestCounter;
		int previousEventSequence;
		int pickupPredictionTime;
		float lightingOrigin[3];
		XAnimTree_s* tree;
		centity_s* updateDelayedNext;
	};

	// Unknown what it's real name is
	struct cgEntity_s
	{
		centity_s entity;
		int unkown;
	};

	static_assert(sizeof(entityState_s) == 0x100);
	static_assert(sizeof(centity_s) == 0x200);
	static_assert(sizeof(cgEntity_s) == 0x204);

	struct playerEntity_t
	{
		int bPositionToADS;
		float fLastIdleFactor;
		float baseMoveOrigin[3];
		float baseMoveAngles[3];
	};

	static_assert(sizeof(playerEntity_t) == 0x20);

	enum DemoType
	{
		DEMO_TYPE_NONE = 0x0,
		DEMO_TYPE_CLIENT = 0x1,
		DEMO_TYPE_SERVER = 0x2,
	};

	enum CubemapShot
	{
		CUBEMAPSHOT_NONE = 0x0,
		CUBEMAPSHOT_RIGHT = 0x1,
		CUBEMAPSHOT_LEFT = 0x2,
		CUBEMAPSHOT_BACK = 0x3,
		CUBEMAPSHOT_FRONT = 0x4,
		CUBEMAPSHOT_UP = 0x5,
		CUBEMAPSHOT_DOWN = 0x6,
		CUBEMAPSHOT_COUNT = 0x7,
	};

	struct snapshot_s
	{
		playerState_s ps;
		int snapFlags;
		int ping;
		int serverTime;
		int numEntities;
		int numClients;
		entityState_s entities[768];
		clientState_s clients[18];
		int serverCommandSequence;
	};

	static_assert(sizeof(snapshot_s) == 0x339EC);

	struct RefdefView
	{
		float tanHalfFovX;
		float tanHalfFovY;
		float org[3];
		float axis[3][3];
		float zNear;
	};

	struct refdef_t
	{
		unsigned int x;
		unsigned int y;
		unsigned int width;
		unsigned int height;
		RefdefView view;
		float viewOffset[3];
		int time;
		float blurRadius;
		GfxDepthOfField dof;
		GfxFilm film;
		GfxGlow glow;
		GfxLightScale charPrimaryLightScale;
		GfxCompositeFx waterSheetingFx;
		GfxLight primaryLights[248];
		GfxViewport scissorViewport;
		bool useScissorViewport;
		bool viewModelHasDistortion;
		char forceSunShadowsGenerate;
		bool halfResParticles;
		bool playerTeleported;
		int localClientNum;
	};

	struct cg_s
	{
		playerState_s predictedPlayerState;
		centity_s predictedPlayerEntity;
		playerEntity_t playerEntity;
		int predictedErrorTime;
		float predictedError[3];
		int clientNum;
		int localClientNum;
		DemoType demoType;
		CubemapShot cubemapShot;
		int cubemapSize;
		int renderScreen;
		int latestSnapshotNum;
		int latestSnapshotTime;
		char pad0[4];
		snapshot_s* snap;
		snapshot_s* nextSnap;
		snapshot_s activeSnapshots[2];
		float frameInterpolation;
		int frametime;	// + 0x6A754
		int time;
		int oldTime;
		int physicalsTime;
		int mapRestart;
		int renderingThirdPerson;
		float landChange;
		int landTime;
		float heightToCeiling;
		refdef_t refdef;
		float refdefViewAngles[3];
		float baseGunAngles[3];
		float aimAssistEyeOrigin[3];
		float aimAssistViewOrigin[3];
		float aimAssistViewAngles[3];
		float thirdPersonGunPitch;
		float thirdPersonGunYaw;
		float thirdPersonAdsLerp;
		float swayViewAngles[3];
		float swayAngles[3];
		float swayOffset[3];
		float recoilAngles[3];
		float recoilSpeed[3];
		char _pad2[18600];
		int weaponSelect;
		int weaponSelectTime;
		char _pad3[3416];
		float compassMapWorldSize[2]; // + 0x73D64
		char _pad4[0x74]; // + 0x73D6C
		float selectedLocation[2]; // + 0x73DE0
		float selectedLocationAngle;
		float selectedAngleLocation[2];
		float selectedLocationPrev[2];
		float selectedLocationAnglePrev;
		char _pad5[0x89740];
	};

	static_assert(sizeof(cg_s) == 0xFD540);
	static_assert(offsetof(cg_s, predictedPlayerEntity) == 0x311C);
	static_assert(offsetof(cg_s, playerEntity) == 0x331C);
	static_assert(offsetof(cg_s, cubemapShot) == 0x3358);
	static_assert(offsetof(cg_s, nextSnap) == 0x3374); // CONFIRMED CORRECT
	static_assert(offsetof(cg_s, frameInterpolation) == 0x6A750);
	static_assert(offsetof(cg_s, refdef) == 0x6A778); // CONFIRMED CORRECT
	static_assert(offsetof(cg_s, refdefViewAngles) == 0x6E6D8);
	static_assert(offsetof(cg_s, compassMapWorldSize) == 0x73D64);
	static_assert(offsetof(cg_s, selectedLocation) == 0x73DE0);

	static constexpr auto MAX_GPAD_COUNT = 1;

	static constexpr auto GPAD_VALUE_MASK = 0xFFFFFFFu;
	static constexpr auto GPAD_DPAD_MASK = XINPUT_GAMEPAD_DPAD_UP | XINPUT_GAMEPAD_DPAD_DOWN | XINPUT_GAMEPAD_DPAD_LEFT | XINPUT_GAMEPAD_DPAD_RIGHT;
	static constexpr auto GPAD_DIGITAL_MASK = 1u << 28;
	static constexpr auto GPAD_ANALOG_MASK = 1u << 29;
	static constexpr auto GPAD_STICK_MASK = 1u << 30;

	enum GamePadButton
	{
		GPAD_NONE = 0,
		GPAD_UP = GPAD_DIGITAL_MASK | (XINPUT_GAMEPAD_DPAD_UP & GPAD_VALUE_MASK),
		GPAD_DOWN = GPAD_DIGITAL_MASK | (XINPUT_GAMEPAD_DPAD_DOWN & GPAD_VALUE_MASK),
		GPAD_LEFT = GPAD_DIGITAL_MASK | (XINPUT_GAMEPAD_DPAD_LEFT & GPAD_VALUE_MASK),
		GPAD_RIGHT = GPAD_DIGITAL_MASK | (XINPUT_GAMEPAD_DPAD_RIGHT & GPAD_VALUE_MASK),
		GPAD_START = GPAD_DIGITAL_MASK | (XINPUT_GAMEPAD_START & GPAD_VALUE_MASK),
		GPAD_BACK = GPAD_DIGITAL_MASK | (XINPUT_GAMEPAD_BACK & GPAD_VALUE_MASK),
		GPAD_L3 = GPAD_DIGITAL_MASK | (XINPUT_GAMEPAD_LEFT_THUMB & GPAD_VALUE_MASK),
		GPAD_R3 = GPAD_DIGITAL_MASK | (XINPUT_GAMEPAD_RIGHT_THUMB & GPAD_VALUE_MASK),
		GPAD_L_SHLDR = GPAD_DIGITAL_MASK | (XINPUT_GAMEPAD_LEFT_SHOULDER & GPAD_VALUE_MASK),
		GPAD_R_SHLDR = GPAD_DIGITAL_MASK | (XINPUT_GAMEPAD_RIGHT_SHOULDER & GPAD_VALUE_MASK),
		GPAD_A = GPAD_DIGITAL_MASK | (XINPUT_GAMEPAD_A & GPAD_VALUE_MASK),
		GPAD_B = GPAD_DIGITAL_MASK | (XINPUT_GAMEPAD_B & GPAD_VALUE_MASK),
		GPAD_X = GPAD_DIGITAL_MASK | (XINPUT_GAMEPAD_X & GPAD_VALUE_MASK),
		GPAD_Y = GPAD_DIGITAL_MASK | (XINPUT_GAMEPAD_Y & GPAD_VALUE_MASK),
		GPAD_L_TRIG = GPAD_ANALOG_MASK | (0 & GPAD_VALUE_MASK),
		GPAD_R_TRIG = GPAD_ANALOG_MASK | (1 & GPAD_VALUE_MASK),
	};

	enum GamePadStick
	{
		GPAD_INVALID = 0x0,
		GPAD_LX = GPAD_STICK_MASK | (0 & GPAD_VALUE_MASK),
		GPAD_LY = GPAD_STICK_MASK | (1 & GPAD_VALUE_MASK),
		GPAD_RX = GPAD_STICK_MASK | (2 & GPAD_VALUE_MASK),
		GPAD_RY = GPAD_STICK_MASK | (3 & GPAD_VALUE_MASK),
	};

	enum GamePadButtonEvent
	{
		GPAD_BUTTON_RELEASED = 0x0,
		GPAD_BUTTON_PRESSED = 0x1,
		GPAD_BUTTON_UPDATE = 0x2,
	};

	enum GamepadPhysicalAxis
	{
		GPAD_PHYSAXIS_NONE = -1,
		GPAD_PHYSAXIS_RSTICK_X = 0x0,
		GPAD_PHYSAXIS_RSTICK_Y = 0x1,
		GPAD_PHYSAXIS_LSTICK_X = 0x2,
		GPAD_PHYSAXIS_LSTICK_Y = 0x3,
		GPAD_PHYSAXIS_RTRIGGER = 0x4,
		GPAD_PHYSAXIS_LTRIGGER = 0x5,

		GPAD_PHYSAXIS_COUNT,
	};

	enum GamepadVirtualAxis
	{
		GPAD_VIRTAXIS_NONE = -1,
		GPAD_VIRTAXIS_SIDE = 0x0,
		GPAD_VIRTAXIS_FORWARD = 0x1,
		GPAD_VIRTAXIS_UP = 0x2,
		GPAD_VIRTAXIS_YAW = 0x3,
		GPAD_VIRTAXIS_PITCH = 0x4,
		GPAD_VIRTAXIS_ATTACK = 0x5,

		GPAD_VIRTAXIS_COUNT
	};

	enum GamePadStickDir
	{
		GPAD_STICK_POS = 0x0,
		GPAD_STICK_NEG = 0x1,

		GPAD_STICK_DIR_COUNT
	};

	enum GamepadMapping
	{
		GPAD_MAP_NONE = -1,
		GPAD_MAP_LINEAR = 0x0,
		GPAD_MAP_SQUARED = 0x1,

		GPAD_MAP_COUNT
	};

	struct ButtonToCodeMap_t
	{
		GamePadButton padButton;
		int code;
	};

	struct StickToCodeMap_t
	{
		GamePadStick padStick;
		int posCode;
		int negCode;
	};

	struct GamepadVirtualAxisMapping
	{
		GamepadPhysicalAxis physicalAxis;
		GamepadMapping mapType;
	};

	struct GpadAxesGlob
	{
		float axesValues[GPAD_PHYSAXIS_COUNT];
		GamepadVirtualAxisMapping virtualAxes[GPAD_VIRTAXIS_COUNT];
	};

	enum weaponstate_t
	{
		WEAPON_READY = 0x0,
		WEAPON_RAISING = 0x1,
		WEAPON_RAISING_ALTSWITCH = 0x2,
		WEAPON_DROPPING = 0x3,
		WEAPON_DROPPING_QUICK = 0x4,
		WEAPON_DROPPING_ALT = 0x5,
		WEAPON_FIRING = 0x6,
		WEAPON_RECHAMBERING = 0x7,
		WEAPON_RELOADING = 0x8,
		WEAPON_RELOADING_INTERUPT = 0x9,
		WEAPON_RELOAD_START = 0xA,
		WEAPON_RELOAD_START_INTERUPT = 0xB,
		WEAPON_RELOAD_END = 0xC,
		WEAPON_MELEE_INIT = 0xD,
		WEAPON_MELEE_FIRE = 0xE,
		WEAPON_MELEE_END = 0xF,
		WEAPON_OFFHAND_INIT = 0x10,
		WEAPON_OFFHAND_PREPARE = 0x11,
		WEAPON_OFFHAND_HOLD = 0x12,
		WEAPON_OFFHAND_FIRE = 0x13,
		WEAPON_OFFHAND_DETONATE = 0x14,
		WEAPON_OFFHAND_END = 0x15,
		WEAPON_DETONATING = 0x16,
		WEAPON_SPRINT_RAISE = 0x17,
		WEAPON_SPRINT_LOOP = 0x18,
		WEAPON_SPRINT_DROP = 0x19,
		WEAPON_STUNNED_START = 0x1A,
		WEAPON_STUNNED_LOOP = 0x1B,
		WEAPON_STUNNED_END = 0x1C,
		WEAPON_NIGHTVISION_WEAR = 0x1D,
		WEAPON_NIGHTVISION_REMOVE = 0x1E,

		WEAPONSTATES_NUM
	};

	struct AimAssistPlayerState
	{
		float velocity[3];
		int eFlags;
		int linkFlags;
		int pm_flags;
		int weapFlags;
		int weaponState;
		float fWeaponPosFrac;
		int weapIndex;
		bool hasAmmo;
		bool isDualWielding;
		bool isThirdPerson;
		bool isExtendedMelee;
	};

	struct AimTweakables
	{
		float slowdownRegionWidth;
		float slowdownRegionHeight;
		float autoAimRegionWidth;
		float autoAimRegionHeight;
		float autoMeleeRegionWidth;
		float autoMeleeRegionHeight;
		float lockOnRegionWidth;
		float lockOnRegionHeight;
	};

	constexpr auto AIM_TARGET_INVALID = MAX_GENTITIES - 1;
	struct AimScreenTarget
	{
		int entIndex;
		float clipMins[2];
		float clipMaxs[2];
		float aimPos[3];
		float velocity[3];
		float distSqr;
		float crosshairDistSqr;
	};

	enum AutoMeleeState
	{
		AIM_MELEE_STATE_OFF = 0x0,
		AIM_MELEE_STATE_TARGETED = 0x1,
		AIM_MELEE_STATE_UPDATING = 0x2,
	};

#pragma warning(push)
#pragma warning(disable: 4324)
	struct __declspec(align(16)) AimAssistGlobals
	{
		AimAssistPlayerState ps;
		char _pad1[4];
		float screenMtx[4][4];
		float invScreenMtx[4][4];
		bool initialized;
		int prevButtons;
		AimTweakables tweakables;
		float eyeOrigin[3];
		float viewOrigin[3];
		float viewAngles[3];
		float viewAxis[3][3];
		float fovTurnRateScale;
		float fovScaleInv;
		float adsLerp;
		float pitchDelta;
		float yawDelta;
		float screenWidth;
		float screenHeight;
		AimScreenTarget screenTargets[64];
		int screenTargetCount;
		int autoAimTargetEnt;
		bool autoAimPressed;
		bool autoAimActive;
		float autoAimPitch;
		float autoAimPitchTarget;
		float autoAimYaw;
		float autoAimYawTarget;
		AutoMeleeState autoMeleeState;
		int autoMeleeTargetEnt;
		float autoMeleePitch;
		float autoMeleePitchTarget;
		float autoMeleeYaw;
		float autoMeleeYawTarget;
		int lockOnTargetEnt;
	};
#pragma warning(pop)

	enum ShockViewTypes
	{
		SHELLSHOCK_VIEWTYPE_BLURRED = 0x0,
		SHELLSHOCK_VIEWTYPE_FLASHED = 0x1,
		SHELLSHOCK_VIEWTYPE_NONE = 0x2,
	};

	struct shellshock_parms_t
	{
		struct
		{
			int blurredFadeTime;
			int blurredEffectTime;
			int flashWhiteFadeTime;
			int flashShotFadeTime;
			ShockViewTypes type;
		} screenBlend;

		struct
		{
			int fadeTime;
			float kickRate;
			float kickRadius;
		} view;

		struct
		{
			bool affect;
			char loop[64];
			char loopSilent[64];
			char end[64];
			char endAbort[64];
			int fadeInTime;
			int fadeOutTime;
			float drylevel;
			float wetlevel;
			char roomtype[16];
			float channelvolume[64];
			int modEndDelay;
			int loopFadeTime;
			int loopEndDelay;
		} sound;

		struct
		{
			bool affect;
			int fadeTime;
			float mouseSensitivity;
			float maxPitchSpeed;
			float maxYawSpeed;
		} lookControl;

		struct
		{
			bool affect;
		} movement;
	};

	struct animation_s
	{
		char name[MAX_QPATH];
		int initialLerp;
		float moveSpeed;
		int duration;
		int nameHash;
		int flags;
		int64_t movetype;
		int noteType;
	};

	struct lerpFrame_t
	{
		float yawAngle;
		int yawing;
		float pitchAngle;
		int pitching;
		int animationNumber;
		animation_s* animation;
		int animationTime;
		float oldFramePos[3];
		float animSpeedScale;
		int oldFrameSnapshotTime;
	};

	enum PlayerDiveState
	{
		DIVE_NONE = 0x0,
		DIVE_FORWARD = 0x1,
		DIVE_FORWARDLEFT = 0x2,
		DIVE_LEFT = 0x3,
		DIVE_BACKLEFT = 0x4,
		DIVE_BACK = 0x5,
		DIVE_BACKRIGHT = 0x6,
		DIVE_RIGHT = 0x7,
		DIVE_FORWARDRIGHT = 0x8,
	};

	struct clientInfo_t
	{
		int infoValid;
		int nextValid;
		int clientNum;
		char name[16];
		team_t team;
		team_t oldteam;
		int rank;
		int prestige;
		unsigned int perks[2];
		int score;
		int location;
		int health;
		char model[64];
		char attachModelNames[6][64];
		char attachTagNames[6][64];
		unsigned int partBits[6];
		lerpFrame_t legs;
		lerpFrame_t torso;
		float lerpMoveDir;
		float lerpLean;
		float playerAngles[3];
		int legsAnim;
		int torsoAnim;
		float fTorsoPitch;
		float fWaistPitch;
		int leftHandGun;
		int dobjDirty;
		clientControllers_t control;
		unsigned int clientConditions[18][2];
		XAnimTree_s* pXAnimTree;
		int iDObjWeapon;
		char weaponModel;
		int stanceTransitionTime;
		int turnAnimEndTime;
		char turnAnimType;
		bool hideWeapon;
		bool usingKnife;
		int dualWielding;
		PlayerDiveState diveState;
		int riotShieldNext;
		unsigned int playerCardIcon;
		unsigned int playerCardTitle;
		unsigned int playerCardNameplate;
	};

	static_assert(sizeof(clientInfo_t) == 0x52C);

	struct cgs_t
	{
		int viewX;
		int viewY;
		int viewWidth;
		int viewHeight;
		float viewAspect;
		int serverCommandSequence;
		int processedSnapshotNum;
		int localServer;
		char gametype[32];
		char szHostName[256];
		bool hardcore;
		int maxclients;
		int privateClients;
		char mapname[64];
		int gameEndTime;
		int voteTime;
		int voteYes;
		int voteNo;
		char voteString[256];
		XModel* gameModels[512];
		FxEffectDef* smokeGrenadeFx;
		shellshock_parms_t holdBreathParams;
		char teamChatMsgs[8][160];
		int teamChatMsgTimes[8];
		int teamChatPos;
		int teamLastChatPos;
		float compassWidth;
		float compassHeight;
		float compassY;
		clientInfo_t corpseinfo[8];
		bool entUpdateToggleContextKey;
		XAnim_s* helicopterAnims;
	};

	static_assert(sizeof(cgs_t) == 0x3BA4);

	struct ConversionArguments
	{
		int argCount;
		const char* args[9];
	};

	enum TraceHitType
	{
		TRACE_HITTYPE_NONE = 0,
		TRACE_HITTYPE_ENTITY = 1,
		TRACE_HITTYPE_DYNENT_MODEL = 2,
		TRACE_HITTYPE_DYNENT_BRUSH = 3,
		TRACE_HITTYPE_GLASS = 4
	};

	struct trace_t
	{
		float fraction;
		float normal[3];
		int surfaceFlags;
		int contents;
		const char* material;
		TraceHitType hitType;
		unsigned __int16 hitId;
		unsigned __int16 modelIndex;
		unsigned __int16 partName;
		unsigned __int16 partGroup;
		bool allsolid;
		bool startsolid;
		bool walkable;
	};

	static_assert(sizeof(trace_t) == 0x2C);

	struct pmove_s
	{
		playerState_s* ps;
		usercmd_s cmd;
		usercmd_s oldcmd;
		int tracemask; // 84
		int numtouch;
		int touchents[32];
		Bounds bounds; // 220
		float xyspeed;
		int proneChange;
		float maxSprintTimeMultiplier;
		bool mantleStarted;
		float mantleEndPos[3];
		int mantleDuration;
		int viewChangeTime;
		float viewChange;
		float fTorsoPitch;
		float fWaistPitch;
		unsigned char handler;
	};


	static_assert(sizeof(pmove_s) == 296);

	struct pml_t
	{
		float forward[3];
		float right[3];
		float up[3];
		float frametime;
		int msec;
		int walking;
		int groundPlane;
		int almostGroundPlane;
		trace_t groundTrace;
		float impactSpeed;
		float previous_origin[3];
		float previous_velocity[3];
		int holdrand;
	};

	static_assert(sizeof(pml_t) == 0x84);

	enum EffectiveStance
	{
		PM_EFF_STANCE_DEFAULT = 0,
		PM_EFF_STANCE_PRONE = 1,
		PM_EFF_STANCE_DUCKED = 2,
		PM_EFF_STANCE_LASTSTANDCRAWL = 3,
		PM_EFF_STANCE_COUNT = 4
	};

	enum entity_event_t
	{
		EV_NONE = 0x0,
		EV_FOLIAGE_SOUND = 0x1,
		EV_STOP_WEAPON_SOUND = 0x2,
		EV_SOUND_ALIAS = 0x3,
		EV_SOUND_ALIAS_AS_MASTER = 0x4,
		EV_STOPSOUNDS = 0x5,
		EV_STANCE_FORCE_STAND = 0x6,
		EV_STANCE_FORCE_CROUCH = 0x7,
		EV_STANCE_FORCE_PRONE = 0x8,
		EV_STANCE_INVALID = 0x9,
		EV_ITEM_PICKUP = 0xA,
		EV_AMMO_PICKUP = 0xB,
		EV_NOAMMO = 0xC,
		EV_EMPTYCLIP = 0xD,
		EV_EMPTY_OFFHAND_PRIMARY = 0xE,
		EV_EMPTY_OFFHAND_SECONDARY = 0xF,
		EV_OFFHAND_END_NOTIFY = 0x10,
		EV_RESET_ADS = 0x11,
		EV_RELOAD = 0x12,
		EV_RELOAD_FROM_EMPTY = 0x13,
		EV_RELOAD_START = 0x14,
		EV_RELOAD_END = 0x15,
		EV_RELOAD_START_NOTIFY = 0x16,
		EV_RELOAD_ADDAMMO = 0x17,
		EV_RAISE_WEAPON = 0x18,
		EV_FIRST_RAISE_WEAPON = 0x19,
		EV_PUTAWAY_WEAPON = 0x1A,
		EV_WEAPON_ALT = 0x1B,
		EV_WEAPON_SWITCH_STARTED = 0x1C,
		EV_PULLBACK_WEAPON = 0x1D,
		EV_FIRE_WEAPON = 0x1E,
		EV_FIRE_WEAPON_LASTSHOT = 0x1F,
		EV_FIRE_RICOCHET = 0x20,
		EV_RECHAMBER_WEAPON = 0x21,
		EV_EJECT_BRASS = 0x22,
		EV_FIRE_WEAPON_LEFT = 0x23,
		EV_FIRE_WEAPON_LASTSHOT_LEFT = 0x24,
		EV_EJECT_BRASS_LEFT = 0x25,
		EV_HITCLIENT_FIRE_WEAPON = 0x26,
		EV_HITCLIENT_FIRE_WEAPON_LASTSHOT = 0x27,
		EV_HITCLIENT_FIRE_WEAPON_LEFT = 0x28,
		EV_HITCLIENT_FIRE_WEAPON_LASTSHOT_LEFT = 0x29,
		EV_SV_FIRE_WEAPON = 0x2A,
		EV_SV_FIRE_WEAPON_LASTSHOT = 0x2B,
		EV_SV_FIRE_WEAPON_LEFT = 0x2C,
		EV_SV_FIRE_WEAPON_LASTSHOT_LEFT = 0x2D,
		EV_MELEE_SWIPE = 0x2E,
		EV_FIRE_MELEE = 0x2F,
		EV_PREP_OFFHAND = 0x30,
		EV_USE_OFFHAND = 0x31,
		EV_SWITCH_OFFHAND = 0x32,
		EV_MELEE_HIT = 0x33,
		EV_MELEE_MISS = 0x34,
		EV_MELEE_BLOOD = 0x35,
		EV_FIRE_TURRET = 0x36,
		EV_FIRE_SENTRY = 0x37,
		EV_FIRE_QUADBARREL_1 = 0x38,
		EV_FIRE_QUADBARREL_2 = 0x39,
		EV_BULLET_HIT = 0x3A,
		EV_BULLET_HIT_EXPLODE = 0x3B,
		EV_BULLET_HIT_SHIELD = 0x3C,
		EV_BULLET_HIT_CLIENT_SMALL = 0x3D,
		EV_BULLET_HIT_CLIENT_LARGE = 0x3E,
		EV_BULLET_HIT_CLIENT_EXPLODE = 0x3F,
		EV_BULLET_HIT_CLIENT_SHIELD = 0x40,
		EV_EXPLOSIVE_IMPACT_ON_SHIELD = 0x41,
		EV_EXPLOSIVE_SPLASH_ON_SHIELD = 0x42,
		EV_GRENADE_BOUNCE = 0x43,
		EV_GRENADE_STICK = 0x44,
		EV_GRENADE_REST = 0x45,
		EV_GRENADE_EXPLODE = 0x46,
		EV_GRENADE_PICKUP = 0x47,
		EV_GRENADE_LETGO = 0x48,
		EV_ROCKET_EXPLODE = 0x49,
		EV_ROCKET_EXPLODE_NOMARKS = 0x4A,
		EV_FLASHBANG_EXPLODE = 0x4B,
		EV_CUSTOM_EXPLODE = 0x4C,
		EV_CUSTOM_EXPLODE_NOMARKS = 0x4D,
		EV_CHANGE_TO_DUD = 0x4E,
		EV_DUD_EXPLODE = 0x4F,
		EV_DUD_IMPACT = 0x50,
		EV_TROPHY_EXPLODE = 0x51,
		EV_BULLET = 0x52,
		EV_PLAY_FX = 0x53,
		EV_PLAY_FX_ON_TAG = 0x54,
		EV_STOP_FX_ON_TAG = 0x55,
		EV_PLAY_FX_ON_TAG_FOR_CLIENTS = 0x56,
		EV_PHYS_EXPLOSION_SPHERE = 0x57,
		EV_PHYS_EXPLOSION_CYLINDER = 0x58,
		EV_PHYS_EXPLOSION_JOLT = 0x59,
		EV_RADIUSDAMAGE = 0x5A,
		EV_PHYS_JITTER = 0x5B,
		EV_EARTHQUAKE = 0x5C,
		EV_GRENADE_SUICIDE = 0x5D,
		EV_DETONATE = 0x5E,
		EV_NIGHTVISION_WEAR = 0x5F,
		EV_NIGHTVISION_REMOVE = 0x60,
		EV_MISSILE_REMOTE_BOOST = 0x61,
		EV_OBITUARY = 0x62,
		EV_NO_PRIMARY_GRENADE_HINT = 0x63,
		EV_NO_SECONDARY_GRENADE_HINT = 0x64,
		EV_TARGET_TOO_CLOSE_HINT = 0x65,
		EV_TARGET_NOT_ENOUGH_CLEARANCE_HINT = 0x66,
		EV_LOCKON_REQUIRED_HINT = 0x67,
		EV_VEHICLE_COLLISION = 0x68,
		EV_VEHICLE_SUSPENSION_SOFT = 0x69,
		EV_VEHICLE_SUSPENSION_HARD = 0x6A,
		EV_FOOTSTEP_SPRINT = 0x6B,
		EV_FOOTSTEP_RUN = 0x6C,
		EV_FOOTSTEP_WALK = 0x6D,
		EV_FOOTSTEP_PRONE = 0x6E,
		EV_JUMP = 0x6F,
		EV_LANDING_FIRST = 0x70,
		EV_LANDING_LAST = 0x8E,
		EV_LANDING_PAIN_FIRST = 0x8F,
		EV_LANDING_PAIN_LAST = 0xAD,
		EV_MANTLE = 0xAE,
		EV_DEBUG_SERVER_AIMING = 0xAF,
		EV_MAX_EVENTS = 0xB0,
	};


	struct TempPriority
	{
		void* threadHandle;
		int oldPriority;
	};

	struct FastCriticalSection
	{
		volatile long readCount;
		volatile long writeCount;
		TempPriority tempPriority;
	};

	struct trigger_info_t
	{
		unsigned __int16 entnum;
		unsigned __int16 otherEntnum;
		int useCount;
		int otherUseCount;
	};

	struct com_parse_mark_t
	{
		int lines;
		const char* text;
		int ungetToken;
		int backup_lines;
		const char* backup_text;
	};

	struct cached_tag_mat_t
	{
		int time;
		int entnum;
		unsigned __int16 name;
		float tagMat[4][3];
	};

	struct Turret
	{
		bool inuse;
		int flags;
		int fireTime;
		float arcmin[2];
		float arcmax[2];
		float dropPitch;
		int stance;
		int prevStance;
		int fireSndDelay;
		float userOrigin[3];
		float playerSpread;
		int state;
		EntHandle target;
		float targetOffset[3];
		EntHandle manualTarget;
		float manualTargetOffset[3];
		int targetTime;
		int stateChangeTime;
		int modeChangeTime;
		float maxRangeSquared;
		int prevTargetIndex;
		team_t eTeam;
		int convergenceTime[2];
		float targetPos[3];
		float missOffsetNormalized[3];
		float scanSpeed;
		float scanDecelYaw;
		int scanPauseTime;
		bool triggerDown;
		float heatLevel;
		int heatPenaltyEndTime;
		float barrelRollRate;
		int autoRotationStopDelay;
		int lastAutoRotationRequestTime;
		unsigned __int8 fireSnd;
		unsigned __int8 fireSndPlayer;
		unsigned __int8 stopSnd;
		unsigned __int8 stopSndPlayer;
		unsigned __int8 scanSnd;
	};

	static_assert(sizeof(Turret) == 0xC4);

	struct level_locals_t
	{
		gclient_s* clients;
		gentity_s* gentities;
		int num_entities;
		gentity_s* firstFreeEnt;
		gentity_s* lastFreeEnt;
		Turret* turrets;
		int logFile;
		int initializing;
		int clientIsSpawning;
		objective_t objectives[32];
		int maxclients;
		int framenum;
		int time;
		int previousTime;
		int frametime;
		int startTime;
		int teamScores[4];
		int lastTeammateHealthTime;
		int bUpdateScoresForIntermission;
		bool teamHasRadar[4];
		bool teamRadarBlocked[4];
		int manualNameChange;
		int numConnectedClients;
		int sortedClients[18];
		char voteString[1024];
		char voteDisplayString[1024];
		int voteTime;
		int voteExecuteTime;
		int voteYes;
		int voteNo;
		int numVotingClients;
		SpawnVar spawnVar;
		int savepersist;
		EntHandle droppedWeaponCue[32];
		float fFogOpaqueDist;
		float fFogOpaqueDistSqrd;
		int currentPlayerClone;
		trigger_info_t pendingTriggerList[256];
		trigger_info_t currentTriggerList[256];
		int pendingTriggerListSize;
		int currentTriggerListSize;
		int finished;
		int bPlayerIgnoreRadiusDamage;
		int bPlayerIgnoreRadiusDamageLatched;
		int registerWeapons;
		int bRegisterItems;
		int currentEntityThink;
		void* openScriptIOFileHandles[1];
		char* openScriptIOFileBuffers[1];
		com_parse_mark_t currentScriptIOLineMark[1];
		cached_tag_mat_t cachedTagMat;
		conChannel_t scriptPrintChannel;
		float compassMapUpperLeft[2];
		float compassMapWorldSize[2];
		float compassNorth[2];
		void* vehicles;
		int hudElemLastAssignedSoundID;
	};

	static_assert(sizeof(level_locals_t) == 0x2F78);

	enum ScreenPlacementMode
	{
		SCRMODE_FULL,
		SCRMODE_DISPLAY,
		SCRMODE_INVALID,
		SCRMODE_COUNT,
	};

	struct WinMouseVars_t
	{
		int oldButtonState;
		tagPOINT oldPos;
		bool mouseActive;
		bool mouseInitialized;
	};

	static_assert(sizeof(WinMouseVars_t) == 0x10);

	struct DeferredMsg
	{
		netadr_t addr;
		unsigned char data[1400];
		int datalen;
	};

	static_assert(sizeof(DeferredMsg) == 0x590);

	struct DeferredQueue
	{
		DeferredMsg msgs[16];
		volatile long get;
		volatile long send;
	};

	static_assert(sizeof(DeferredQueue) == 0x5908);

	struct GamerSettingCommonConfig
	{
		float viewSensitivity;
		float snd_volume;
		float blacklevel;
		float gpadButtonLStickDeflect;
		float gpadButtonRStickDeflect;
		float safearea_adjusted_horizontal;
		float safearea_adjusted_vertical;
		int playTimeSP;
		int playTimeMP;
		int playTimeSO;
		int percentCompleteSP;
		int percentCompleteMP;
		int percentCompleteSO;
		float gamma;
		bool hasEverPlayed_MainMenu;
		bool hasEverPlayed_SP;
		bool hasEverPlayed_SO;
		bool hasEverPlayed_MP;
		bool invertPitch;
		bool autoAim;
		bool delicateFlower;
		char gpadButtonsConfig[32];
		char gpadSticksConfig[32];
	};

	struct KeyPairStringData
	{
		short index;
		short maxSize;
	};

	union KeyPairDataUnion
	{
		char byteVal;
		bool boolVal;
		short shortVal;
		int intVal;
		float floatVal;
		KeyPairStringData stringData;
	};

	struct GamerSettingKeyPair
	{
		char type;
		char unused[3];
		KeyPairDataUnion u;
	};

	struct GamerSettingExeConfig
	{
		int playlist;
		bool mapPrefs[16];
		char clanPrefix[5];
	};

	struct GamerSettingState
	{
		bool isProfileLoggedIn;
		bool errorOnRead;
		GamerSettingCommonConfig commonConfig;
		GamerSettingKeyPair commonKeyPairs[50];
		char commonKeyPairsStringPool[512];
		GamerSettingExeConfig exeConfig;
		GamerSettingKeyPair exeKeyPairs[50];
		char exeKeyPairsStringPool[512];
	};

	static_assert(sizeof(GamerSettingState) == 0x7C0);

	struct SessionStaticData
	{
		char* sessionName;
		bool registerUsersWithVoice;
	};

	enum IWNetServerSessionStatus
	{
		SESSION_ONCLIENTONLY = 0x0,
		SESSION_BEINGCREATED = 0x1,
		SESSION_CREATED = 0x2,
		SESSION_BEINGDELETED = 0x3,
	};

	struct IWNetServerInfoAboutPlayer
	{
		bool active;
		__int64 uid;
		char skill;
		char teamIndex;
		int mapPackFlags;
	};

	struct IWNetSessionStatus
	{
		IWNetServerSessionStatus status;
		int sessionId;
		int lastHeartbeatSent;
		bool needsUpdate;
		bool updatingPlayers;
		int newPlayerCount;
		IWNetServerInfoAboutPlayer pendingServerInfoForPlayers[18];
	};

	struct XSESSION_INFO
	{
		XNKID sessionID;
		XNADDR hostAddress;
		XNKEY keyExchangeKey;
	};

	struct ClientInfo
	{
		bool registered;
		bool voiceRegistered;
		unsigned __int64 xuid;
		int natType;
		netadr_t addr;
		int voiceConnectivityBits;
		int lastConnectivityTestTime;
		bool muted;
		bool privateSlot;
	};

	struct NomineeInfo
	{
		int upload;
		int NAT;
		bool onLSP;
		int connectivity;
		int cpuSpeed;
		int avgPing;
	};

	struct RegisteredUser
	{
		bool active;
		unsigned __int64 xuid;
	};

	struct SessionDynamicData
	{
		bool sessionHandle;
		IWNetSessionStatus iwnetServerSessionStatus;
		XSESSION_INFO sessionInfo;
		bool keysGenerated;
		bool sessionStartCalled;
		unsigned __int64 sessionNonce;
		int privateSlots;
		int publicSlots;
		int flags;
		bool qosListenEnabled;
		ClientInfo users[18];
		int voiceConnectivityBits;
		int sessionCreateController;
		int sessionDeleteTime;
		RegisteredUser internalRegisteredUsers[18];
	};

	struct SessionData
	{
		SessionStaticData staticData;
		SessionDynamicData dyn;
	};

	struct BestHostData
	{
		int nominee;
		NomineeInfo info;
		int lastHeardFrom;
		int lastSentTo;
	};

	struct BandwidthTestPerClientData
	{
		int bytesReceived;
	};

	struct BandwidthTestData
	{
		int testIndex;
		int testClientNum;
		int startTimeArbitrator;
		int announceTime;
		int winnerClientNum;
		BandwidthTestPerClientData clientData[18];
		char testClientName[32];
		bool inProgress;
		int startTime;
		int roundsComplete;
		bool receiving;
		int receiveIndex;
		int receiveStartTime;
		int receiveBytes;
		int resultsSendTime;
	};

	struct MigrateData
	{
		bool migrateActive;
		bool weAreArbitrating;
		int arbitratorClientNum;
		int indexBits;
		int startTime;
		int timeoutDuration;
		int lastBroadcastTime;
		bool decidedOurNominee;
		BestHostData bestHost;
		int expectedNewHost;
		BandwidthTestData bandwidthTestData;
	};

	struct QoSData
	{
		float percent;
	};

	struct PartyInfo
	{
		bool active;
		XSESSION_INFO info;
		int occupiedPublicSlots;
		int occupiedPrivateSlots;
		int numPublicSlots;
		int numPrivateSlots;
		int pingBias;
		int ping;
		int upload;
		int desirability;
	};

	struct PartyMember
	{
		char status;
		bool headsetPresent;
		char gamertag[32];
		char clanAbbrev[5];
		int qport;
		char challenge[6];
		int lastPacketTime;
		int lastHeartbeatTime;
		int lastPartyStateAck;
		XNADDR xnaddr;
		int availableMapPackFlags;
		int ackedMembers;
		XNKID privatePartyId;
		int subpartyIndex;
		int trueSkill;
		int rank;
		int prestige;
		int team;
		unsigned __int16 score;
		int deaths;
		bool vetoedMap;
		unsigned int playerCardIcon;
		unsigned int playerCardTitle;
		unsigned int playerCardNameplate;
		int voiceConnectivityBits;
		bool invited;
		int natType;
		unsigned __int64 player;
		bool migrateHeardFrom;
		int migratePingTime;
		int migratePing;
		bool migrateNominated;
		NomineeInfo migrateNomineeInfo;
	};

	struct SubpartyInfo
	{
		int members[18];
		int count;
		int skill;
		int score;
		int team;
	};

	struct PartyHostDetails
	{
		int partyListSlot;
		netadr_t addr;
		XSESSION_INFO sessionInfo;
		int lastPacketTime;
		int lastPacketSentTime;
		int numPrivateSlots;
		int numPublicSlots;
		int hostNum;
		bool accepted;
		char challenge[6];
	};

	struct PartyHostData
	{
		int partyStateChangeTime;
		int partyStateLastSendTime;
		int expectedPlayers;
		int vetoPassTime;
		bool vetoPossible;
		bool preloadingMap;
		bool firstLobby;
		bool migrateAfterRound;
		bool stopAfterRound;
		int partyCreationTime;
	};

	struct PartyData
	{
		SessionData* session;
		SessionData* presenceSession;
		SessionData* searchSession;
		MigrateData migrateData;
		QoSData qosData;
		PartyInfo* partyList;
		int partyListSize;
		PartyMember partyMembers[18];
		SubpartyInfo subparties[18];
		int subpartyCount;
		PartyHostDetails currentHost;
		PartyHostDetails potentialHost;
		PartyHostData hostData;
		unsigned __int64 lobbySteamID;
		int areWeHost;
		int joiningAnotherParty;
		int searchingForGames;
		int inParty;
		int party_systemActive;
		bool veto;
		int vetoTime;
		int headsetPresent;
		int headsetTime;
		int clanAbbrevTime;
		int rankTime;
		int playerCardTime;
		int uploadSentTime;
		int voiceBitsTime;
		int idTime;
		int availableMapPackFlagsTime;
		int searchStartTime;
		int searchEndTime;
		int joinAttemptForUI;
		int lastMergeTime;
		int mergeAttemptStartTime;
		int originalPartiesInList;
		int partyId;
		int nextSessionSearchTime;
		int mapPackFlags;
		int lastPartyStateTime;
		int gameStartTime;
		int interEndTime;
		int inactiveKeepaliveTime;
		int hostTimeouts;
		char lobbyFlags;
		PartyData* partyToNotify;
		bool registeredWithArbitration;
		bool rejoining;
		int partyStatePacketCount;
		int partyStateLastMemberIndex;
		int unfinishedPartServerTimes[2];
		msg_t partyStatePartMsgs[2];
		char partyStatePartMsgBufs[2][1400];
		char lastEntries[8];
		int currentEntry;
		char axisWins;
		char alliesWins;
	};

	static_assert(sizeof(PartyData) == 0x23D8);

	struct MessageLine
	{
		int messageIndex;
		int textBufPos;
		int textBufSize;
		int typingStartTime;
		int lastTypingSoundTime;
		int flags;
	};

	struct Message
	{
		int startTime;
		int endTime;
	};

	struct MessageWindow
	{
		MessageLine* lines;
		Message* messages;
		char* circularTextBuffer;
		int textBufSize;
		int lineCount;
		int padding;
		int scrollTime;
		int fadeIn;
		int fadeOut;
		int textBufPos;
		int firstLineIndex;
		int activeLineCount;
		int messageIndex;
	};

	struct MessageBuffer
	{
		char gamemsgText[4][2048];
		MessageWindow gamemsgWindows[4];
		MessageLine gamemsgLines[4][12];
		Message gamemsgMessages[4][12];
		char miniconText[4096];
		MessageWindow miniconWindow;
		MessageLine miniconLines[100];
		Message miniconMessages[100];
		char errorText[1024];
		MessageWindow errorWindow;
		MessageLine errorLines[5];
		Message errorMessages[5];
	};

	struct Console
	{
		MessageWindow consoleWindow;
		MessageLine consoleLines[1024];
		Message consoleMessages[1024];
		char consoleText[65536];
		char textTempLine[512];
		unsigned int lineOffset;
		int displayLineOffset;
		int prevChannel;
		bool outputVisible;
		int fontHeight;
		int visibleLineCount;
		int visiblePixelWidth;
		float screenMin[2];
		float screenMax[2];
		MessageBuffer messageBuffer[1];
		float color[4];
	};

	enum clientMigState_t
	{
		CMSTATE_INACTIVE = 0x0,
		CMSTATE_OLDHOSTLEAVING = 0x1,
		CMSTATE_LIMBO = 0x2,
		CMSTATE_NEWHOSTCONNECT = 0x3,
		CMSTATE_COUNT = 0x4,
	};

	enum MigrationVerboseState
	{
		MVSTATE_INACTIVE = 0x0,
		MVSTATE_WAITING = 0x1,
		MVSTATE_RATING = 0x2,
		MVSTATE_SENDING = 0x3,
		MVSTATE_MIGRATING = 0x4,
		MVSTATE_COUNT = 0x5,
	};

	enum connstate_t
	{
		CA_DISCONNECTED = 0x0,
		CA_CINEMATIC = 0x1,
		CA_LOGO = 0x2,
		CA_CONNECTING = 0x3,
		CA_CHALLENGING = 0x4,
		CA_CONNECTED = 0x5,
		CA_SENDINGSTATS = 0x6,
		CA_LOADING = 0x7,
		CA_PRIMED = 0x8,
		CA_ACTIVE = 0x9,
	};

	struct MigrationPers
	{
		int time;
		bool stanceHeld;
		StanceState stance;
		StanceState stancePosition;
		int stanceTime;
		int cgameUserCmdWeapon;
		int cgameUserCmdOffHandIndex;
		unsigned int weaponSelect;
		int weaponSelectTime;
		int weaponForcedSelectTime;
		unsigned int weaponLatestPrimaryIdx;
		unsigned __int16 primaryWeaponForAlt[1400];
		int holdBreathTime;
		int holdBreathInTime;
		int holdBreathDelay;
		float holdBreathFrac;
	};

	struct clientUIActive_t
	{
		bool active;
		bool isRunning;
		bool cgameInitialized;
		bool cgameInitCalled;
		unsigned char __pad0[0x9AC];
		int keyCatchers;
		bool displayHUDWithKeycatchUI;
		connstate_t connectionState;
		unsigned char __pad1[0x138];
	};

	static_assert(sizeof(clientUIActive_t) == 0xAF4);

	enum msgLocErrType_t
	{
		LOCMSG_SAFE = 0x0,
		LOCMSG_NOERR = 0x1,
	};

	struct ImageList
	{
		unsigned int count;
		GfxImage* image[8192];
	};

	enum CriticalSection
	{
		CRITSECT_CONSOLE,
		CRITSECT_DEBUG_SOCKET,
		CRITSECT_COM_ERROR,
		CRITSECT_STATMON,
		CRITSECT_ALLOC_MARK,
		CRITSECT_GENERATE_MARK,
		CRITSECT_STREAMED_SOUND,
		CRITSECT_FAKELAG,
		CRITSECT_CLIENT_MESSAGE,
		CRITSECT_CLIENT_CMD,
		CRITSECT_DOBJ_ALLOC,
		CRITSECT_START_SERVER,
		CRITSECT_XANIM_ALLOC,
		CRITSECT_KEY_BINDINGS,
		CRITSECT_FX_VIS,
		CRITSECT_SERVER_MESSAGE,
		CRITSECT_SCRIPT_STRING,
		CRITSECT_RD_BUFFER,
		CRITSECT_SYS_EVENT_QUEUE,
		CRITSECT_GPU_FENCE,
		CRITSECT_FATAL_ERROR,
		CRITSECT_MISSING_ASSET,
		CRITSECT_PHYSICS,
		CRITSECT_LIVE,
		CRITSECT_AUDIO_PHYSICS,
		CRITSECT_LSP,
		CRITSECT_CINEMATIC_UPDATE,
		CRITSECT_CINEMATIC_TARGET_CHANGE_COMMAND,
		CRITSECT_CINEMATIC_TARGET_CHANGE_BACKEND,
		CRITSECT_CINEMATIC_STATUS,
		CRITSECT_CINEMATIC_SERVER,
		CRITSECT_FX_ALLOC,
		CRITSECT_NETTHREAD_OVERRIDE,
		CRITSECT_CBUF,
		CRITSECT_STATS_WRITE,
		CRITSECT_CG_GLASS,
		CRITSECT_SERVER_DEMO_COMPRESS,
		CRITSECT_COM_SET_ERROR_MSG,
		CRITSECT_SOUND_UPDATE,
		CRITSECT_RESET_MODEL_LIGHTING,

		CRITSECT_COUNT,
	}; // May be incorrect

	struct ClientVoicePacket_t
	{
		char data[256];
		int dataSize;
	};

	struct voiceCommunication_t
	{
		ClientVoicePacket_t voicePackets[10];
		int voicePacketCount;
		int voicePacketLastTransmit;
		int packetsPerSec;
		int packetsPerSecStart;
	};

	struct VoicePacket_t
	{
		char talker;
		char data[256];
		int dataSize;
	};

	struct uiInfo_s
	{
		UiContext uiDC;
		int myTeamCount;
		int playerRefresh;
		int playerIndex;
		int timeIndex;
		int previousTimes[4];
		uiMenuCommand_t currentMenuType;
		bool allowScriptMenuResponse;
		char findPlayerName[1024];
		char foundPlayerServerAddresses[16][64];
		char foundPlayerServerNames[16][64];
		int numFoundPlayerServers;
		int nextFindPlayerRefresh;
		unsigned int mailUpdateTime;
		char mailIndices[64];
		int mailCount;
		int selectedMail;
	};

	enum entityType_t
	{
		ET_GENERAL = 0x0,
		ET_PLAYER = 0x1,
		ET_PLAYER_CORPSE = 0x2,
		ET_ITEM = 0x3,
		ET_MISSILE = 0x4,
		ET_INVISIBLE = 0x5,
		ET_SCRIPTMOVER = 0x6,
		ET_SOUND_BLEND = 0x7,
		ET_FX = 0x8,
		ET_LOOP_FX = 0x9,
		ET_PRIMARY_LIGHT = 0xA,
		ET_TURRET = 0xB,
		ET_HELICOPTER = 0xC,
		ET_PLANE = 0xD,
		ET_VEHICLE = 0xE,
		ET_VEHICLE_COLLMAP = 0xF,
		ET_VEHICLE_CORPSE = 0x10,
		ET_VEHICLE_SPAWNER = 0x11,
		ET_EVENTS = 0x12,
	};

	struct GfxBackEndPrimitiveData
	{
		int hasSunDirChanged;
	};

	struct GfxFog
	{
		int startTime;
		int finishTime;
		GfxColor color;
		float fogStart;
		float density;
		float fogMaxOpacity;
		bool sunFogEnabled;
		GfxColor sunColor;
		float sunDir[3];
		float sunBeginFadeAngle;
		float sunEndFadeAngle;
		float sunFogScale;
	};

	struct GfxCmdHeader
	{
		unsigned __int16 id;
		unsigned __int16 byteCount;
	};

	struct GfxCmdArray
	{
		char* cmds;
		int usedTotal;
		int usedCritical;
		GfxCmdHeader* lastCmd;
	};

	struct GfxCmdBuf
	{
		IDirect3DDevice9* device;
	};

	struct GfxDrawCallOutput
	{
		GfxCmdBuf cmdBuf;
	};

	struct __declspec(align(4)) GfxDebugPoly
	{
		float color[4];
		int firstVert;
		int vertCount;
		bool outline;
	};

	struct GfxDebugPlume
	{
		float origin[3];
		float color[4];
		int score;
		int startTime;
		int duration;
	};

	struct DebugGlobals
	{
		float(*verts)[3];
		int vertCount;
		int vertLimit;
		GfxDebugPoly* polys;
		int polyCount;
		int polyLimit;
		trDebugString_t* strings;
		int stringCount;
		int stringLimit;
		trDebugString_t* externStrings;
		int externStringCount;
		int externMaxStringCount;
		trDebugLine_t* lines;
		int lineCount;
		int lineLimit;
		trDebugLine_t* externLines;
		int externLineCount;
		int externMaxLineCount;
		GfxDebugPlume* plumes;
		int plumeCount;
		int plumeLimit;
	};

	struct GfxSunShadowProjection
	{
		float switchPartition[4];
		float shadowmapScale[4];
	};

	struct GfxSunShadowOverlaySetup
	{
		float shadowOrg[2];
		float frustumShadowRays[4][2];
		unsigned int clipPlaneCount[2];
		float clipPlanes[2][8][3];
	};

	struct GfxViewportParms
	{
		GfxViewport viewport;
		GfxViewParms viewParms;
	};

	struct GfxSunShadowPartition
	{
		GfxViewportParms viewportParms;
	};

	struct GfxSunShadow
	{
		GfxMatrix lookupMatrix;
		GfxSunShadowProjection sunProj;
		GfxSunShadowPartition partition[2];
		GfxSunShadowOverlaySetup overlaySetup;
	};

	struct GfxSpotShadowSceneLight
	{
		GfxMatrix lookupMatrix;
		float fade;
		GfxImage* image;
	};

	struct GfxDrawSurfIter
	{
		GfxDrawSurf* current;
		GfxDrawSurf* end;
		GfxDrawSurf* mark;
	};

	struct GfxCodeSurfIter
	{
		GfxCodeSurf* current;
		GfxCodeSurf* end;
		GfxCodeSurf* mark;
	};

	struct GfxMarkSurfIter
	{
		GfxMarkSurf* current;
		GfxMarkSurf* end;
		GfxMarkSurf* mark;
	};

	struct GfxGlassSurfIter
	{
		GfxGlassSurf* current;
		GfxGlassSurf* end;
		GfxGlassSurf* mark;
	};

	struct GfxCloudSurfIter
	{
		GfxCloudSurf* current;
		GfxCloudSurf* end;
		GfxCloudSurf* mark;
	};

	struct GfxSparkSurfIter
	{
		GfxSparkSurf* current;
		GfxSparkSurf* end;
		GfxSparkSurf* mark;
	};

	struct GfxSModelSurfIter
	{
		const char* visData;
		unsigned __int16* current;
		const char* end;
		const char* mark;
	};

	struct GfxBspSurfIter
	{
		const unsigned __int16* current;
		const unsigned __int16* end;
		const unsigned __int16* mark;
	};

	struct GfxBspLightMapSurfIter : GfxBspSurfIter
	{
	};

	struct GfxPreTessSurfIter
	{
		GfxPreTessSurf* current;
		GfxPreTessSurf* end;
		GfxPreTessSurf* mark;
	};

	struct GfxSunShadowClip
	{
		unsigned int planeCount[2];
		unsigned int frustumPlaneCount[2];
		DpvsPlane planes[2][10];
	};

	struct GfxSModelCachedSurfIter : GfxSModelSurfIter
	{
	};

	struct GfxSModelRigidSurfIter : GfxSModelSurfIter
	{
	};

	struct GfxSModelSkinnedSurfIter : GfxSModelSurfIter
	{
	};

	struct GfxSModelPreTessSurfIter : GfxSModelSurfIter
	{
	};

	struct GfxCmdRingBuf
	{
		struct GfxDrawListIter* drawListIter;
		unsigned int memoryPos;
		unsigned int maxMemoryPos;
		char* memoryPool;
		unsigned int fencePosIndex;
		volatile unsigned int fenceIndex;
		unsigned int availIndex;
		unsigned int availMemoryPos;
		unsigned int reserveMemoryPos0;
		unsigned int reserveMemoryPos1;
		unsigned int fencePos[64];
		unsigned int fence[64];
		unsigned int checkMemoryPos;
	};

	struct GfxDrawListIter
	{
		GfxBspSurfIter bspSurfIter;
		GfxPreTessSurfIter bspPreTessSurfIter;
		GfxSModelRigidSurfIter smodelRigidSurfIter;
		GfxSModelSkinnedSurfIter smodelSkinnedSurfIter;
		GfxSModelCachedSurfIter smodelCachedSurfIter;
		GfxSModelPreTessSurfIter smodelPreTessSurfIter;
		GfxDrawSurfIter drawSurfIter;
		GfxCodeSurfIter codeSurfIter;
		GfxMarkSurfIter markSurfIter;
		GfxGlassSurfIter glassSurfIter;
		GfxCloudSurfIter cloudSurfIter;
		GfxSparkSurfIter sparkSurfIter;
	};

	union GfxSurfsIteratorSortKey
	{
		struct
		{
			unsigned int spliceIndex;
			unsigned int sortKey;
		} fields;
		unsigned __int64 packed;
	};

	struct GfxSpotShadow
	{
		GfxSpotShadowSceneLight sceneLight;
		GfxViewportParms viewportParms;
		char sceneLightIndex;
		char pad[3];
		GfxLight* light;
		GfxRenderTargetId renderTargetId;
		float pixelAdjust[4];
		int clearScreen;
		GfxMeshData* clearMesh;
	};

	struct GfxDrawListArgs
	{
		GfxCmdBufContext context;
		GfxDrawListInfo* listInfo;
	};

	struct GfxSurfsIterator
	{
		GfxSurfsIteratorSortKey key;
		unsigned int(__cdecl* GetSortKeyCallback)(GfxDrawListIter*);
		bool(__cdecl* RenderDrawGroupCallback)(GfxDrawListArgs*, GfxDrawListIter*);
	};

	struct GfxSurfsIterGroup
	{
		unsigned int iteratorBegin;
		unsigned int iteratorCount;
		GfxDrawListIter drawListIter;
		GfxSurfsIterator iteratorPool[11];
	};

	struct GfxSpliceSurfs
	{
		unsigned int iteratorBegin;
		unsigned int iteratorCount;
		unsigned int spliceCount;
		GfxDrawListIter drawListIter[5];
		GfxViewport scissorViewport[5];
		int isSceneScissorViewport[5];
		GfxDrawListInfo* dynLightDrawListInfo[5];
		GfxSurfsIterator iteratorPool[55];
	};

	struct GfxStaticModelDrawStream
	{
		GfxSModelSurfIter* smodelSurfIter;
		GfxSModelSurfHeader smodelSurfHeader;
		const char* smodelSurfVisData;
		GfxTexture* reflectionProbeTexture;
		unsigned int customSamplerFlags;
		XSurface* localSurf;
		unsigned int smodelCount;
		const unsigned __int16* smodelList;
	};

	struct FxSparkMeshData
	{
		unsigned int triCount;
		unsigned __int16* indices;
		unsigned int baseVertex;
		char pad[4];
		GfxParticleCloud cloud;
	};

	struct SkyOverride
	{
		int isActive;
		float refPos[3];
		float ambientColor[3];
	};

	union PackedLightingCoords
	{
		unsigned int packed;
		char array[4];
	};

	struct GfxSModelCachedVertex
	{
		float xyz[3];
		GfxColor color;
		PackedTexCoords texCoord;
		PackedUnitVec normal;
		PackedUnitVec tangent;
		PackedLightingCoords baseLighting;
	};

	struct GfxBackEndData
	{
		char sceneLightTechType[13][256];
		GfxSparkSurf sparkSurfs[64];
		GfxViewParms viewParms[4];
		GfxMeshData mesh[5];
		GfxSModelCachedVertex smcPatchVerts[8192];
		unsigned __int16 smcPatchList[256];
		unsigned int smcPatchCount;
		unsigned int smcPatchVertsUsed;
		volatile int modelLightingPatchCount;
		SkyOverride skyOverride;
		int localClientNum;
		GfxBackEndPrimitiveData prim;
		volatile int bspSurfDataUsed;
		volatile int smodelSurfDataUsed;
		volatile int smodelSurfVisDataUsed;
		unsigned int sceneLightHasShadowMap[8];
		int drawSurfCount;
		volatile int surfPos;
		volatile int gfxEntCount;
		unsigned int codeSurfCount[2];
		unsigned int codeSurfArgsCount[2];
		volatile int cloudDataCount;
		unsigned int glassSurfCount;
		unsigned int markSurfCount;
		volatile int sparkSurfCount;
		GfxVertexBufferState* skinnedCacheVb;
		unsigned int endFence;
		unsigned int endFrameFence;
		int viewParmCount;
		GfxFog fogSettings;
		GfxCmdArray* commands;
		unsigned int viewInfoIndex;
		unsigned int viewInfoCount;
		GfxViewInfo* viewInfo;
		const void* cmds;
		float sunShadowLightDir[3];
		int hasApproxSunDirChanged;
		int cmdBufValid[18];
		GfxDrawCallOutput drawOutput[18];
		DebugGlobals debugGlobals;
		unsigned int imageRendered[112];
		unsigned int drawType;
		GfxDrawList dynLightDrawList[4];
		unsigned int dynLightCount;
		GfxDrawList* emissiveSpotShadowDrawList[1];
		unsigned int emissiveSpotLightCount;
		GfxSunShadow sunShadow;
		unsigned int spotShadowCount;
		GfxSpotShadow spotShadows[4];
		GfxSurfsIterGroup prepassIterGroup[5];
		GfxSpliceSurfs litTransSpliceSurfs;
		char surfsBuffer[131072];
		float codeSurfArgs[288][4];
		GfxCodeSurf codeEmissiveSurfs[2048];
		GfxCodeSurf codeTransSurfs[640];
		GfxMarkSurf markSurfs[1536];
		GfxGlassSurf glassSurfs[768];
		unsigned __int16 bspSurfData[35328];
		char smodelSurfData[35840];
		char smodelSurfVisData[45056];
		GfxCloudSurf cloudSurfs[256];
		GfxEntity gfxEnts[128];
		FxSparkMeshData sparkData[64];
		GfxParticleCloud cloudData[256];
		GfxDrawSurf drawSurfs[16384];
		GfxLight sceneLights[253];
	};


	struct RumbleDevguiGraphInfo
	{
		struct RumbleInfo* rumbleInfo;
		struct RumbleGraph* rumbleGraph;
	};

	enum DevEventType
	{
		EVENT_ACTIVATE = 0x0,
		EVENT_DEACTIVATE = 0x1,
		EVENT_ACCEPT = 0x2,
		EVENT_UPDATE = 0x3,
		EVENT_DRAW = 0x4,
		EVENT_SAVE = 0x5,
	};

	struct __declspec(align(4)) DevGraph
	{
		float(*knots)[2];
		unsigned __int16* knotCount;
		unsigned __int16 knotCountMax;
		int selectedKnot;
		void(__cdecl* eventCallback)(DevGraph*, DevEventType, int);
		void(__cdecl* textCallback)(DevGraph*, const float, const float, char*, const int);
		void* data;
		bool disableEditingEndPoints;
	};

	struct RumbleGraph
	{
		char graphName[64];
		float knots[16][2];
		unsigned __int16 knotCount;
		DevGraph devguiGraph;
		RumbleDevguiGraphInfo devguiGraphInfo;
	};

	static_assert(sizeof(RumbleGraph) == 236);

	struct RumbleInfo
	{
		int rumbleNameIndex;
		float duration;
		float range;
		RumbleGraph* highRumbleGraph;
		RumbleGraph* lowRumbleGraph;
		int fadeWithDistance;
		int broadcast;
		dvar_t* durationDvar;
		dvar_t* loopDvar;
	};

	static_assert(sizeof(RumbleInfo) == 36);


	union RumbleSource
	{
		int entityNum;
		float pos[3];
	};

	struct ActiveRumble
	{
		RumbleInfo* rumbleInfo;
		int startTime;
		bool loop;
		RumbleSourceType sourceType;
		unsigned char scale;
		RumbleSource source;
	};

	struct RumbleGlobals
	{
		RumbleGraph graphs[64];
		RumbleInfo infos[32];
		ActiveRumble activeRumbles[32];
		float receiverPos[3];
		int receiverEntNum;
	};

	struct GfxSModelCachePageUsage
	{
		unsigned int pageCount;
		unsigned int leftOverVerts;
	};

	struct GfxSModelCacheRowUsage
	{
		unsigned int bucketsUsed[6][25];
		GfxSModelCachePageUsage pageUsage[6];
	};

	struct SModelCacheLeafList
	{
		unsigned __int16 nextIndex;
		unsigned __int16 prevIndex;
	};

	struct SModelCachePageList
	{
		SModelCachePageList* next;
		SModelCachePageList* prev;
	};

	struct SModelCachePage
	{
		SModelCachePageList mru;
		unsigned int rootDivisor;
		unsigned int activeSurfCount;
		unsigned int usedFrameCount;
	};

	struct SModelCacheBucketStats
	{
		unsigned __int16 lodCount;
		unsigned __int16 surfCount;
	};

	struct $A998929642405B21ECC27F960A6EC9DC
	{
		unsigned __int16 smodelIndex;
		char lodIndex;
		char bucketIndex;
	};

	union GfxCachedSModelSurfId
	{
		$A998929642405B21ECC27F960A6EC9DC fields;
		unsigned int packed;
	};

	struct GfxCachedSModelSurf
	{
		GfxCachedSModelSurfId id;
		unsigned int baseVertIndex;
	};

	struct SModelCacheGlobals
	{
		GfxCachedSModelSurf cachedSurfs[24576];
		unsigned int lastUsedFrame[24576];
		SModelCacheLeafList leafList[24876];
		SModelCachePage pages[192];
		SModelCachePageList mruList[6];
		unsigned int ranGarbageCollectorFrame[6][25];
		unsigned int bucketLimit[6][25];
		int isTooFull[6];
		SModelCacheBucketStats bucketStats[6][25];
	};

	enum
	{
		THREAD_VALUE_PROF_STACK = 0x0,
		THREAD_VALUE_VA = 0x1,
		THREAD_VALUE_COM_ERROR = 0x2,
		THREAD_VALUE_TRACE = 0x3,
		THREAD_VALUE_COUNT = 0x4,
	};

	struct va_info_t
	{
		char va_string[2][1024];
		int index;
	};

	struct ProfileAtom
	{
		unsigned int value[1];
	};

	volatile struct ProfileReadable
	{
		unsigned int hits;
		ProfileAtom total;
		ProfileAtom self;
	};

	struct ProfileWritable
	{
		int nesting;
		unsigned int hits;
		ProfileAtom start[3];
		ProfileAtom total;
		ProfileAtom child;
	};

	struct profile_t
	{
		ProfileWritable write;
		ProfileReadable read;
	};

	struct profile_guard_t
	{
		int id;
		profile_t** ppStack;
	};

	struct ProfileStack
	{
		profile_t prof_root;
		profile_t* prof_pStack[16384];
		profile_t** prof_ppStack;
		profile_t prof_array[443];
		ProfileAtom prof_overhead_internal;
		ProfileAtom prof_overhead_external;
		profile_guard_t prof_guardstack[32];
		int prof_guardpos;
		float prof_timescale;
	};

	struct bgs_t
	{
		unsigned char __pad0[0x82950];
	};

	static_assert(sizeof(bgs_t) == 0x82950);

	struct ZipInfo
	{
		int offsetCount;
		int offsets[128];
		int size;
		char* buffer;
	};

	struct Sys_File
	{
		HANDLE handle;
	};

	struct FxCamera
	{
		float origin[3];
		volatile int isValid;
		float frustum[6][4];
		float axis[3][3];
		unsigned int frustumPlaneCount;
		float viewOffset[3];
		bool thermal;
		unsigned int pad[2];
	};

	struct r_double_index_t
	{
		unsigned __int16 value[2];
	};

	struct FxSpriteInfo
	{
		r_double_index_t* indices;
		unsigned int indexCount;
		Material* material;
		const char* name;
	};

	struct FxVisBlocker
	{
		float origin[3];
		unsigned __int16 radius;
		unsigned __int16 visibility;
	};

	struct FxVisState
	{
		FxVisBlocker blocker[256];
		volatile int blockerCount;
		unsigned int pad[3];
	};

	struct FxElem
	{
		char defIndex;
		char sequence;
		char atRestFraction;
		char emitResidual;
		unsigned __int16 nextElemHandleInEffect;
		unsigned __int16 prevElemHandleInEffect;
		int msecBegin;
		float baseVel[3];
		union
		{
			int physObjId;
			float origin[3];
		} ___u8;
		union
		{
			unsigned __int16 lightingHandle;
			unsigned __int16 sparkCloudHandle;
			unsigned __int16 sparkFountainHandle;
		} u;
	};

	struct FxSystem
	{
		FxCamera camera;
		FxCamera cameraPrev;
		FxSpriteInfo sprite;
		FxEffect* effects;
		FxElem* elems;
		void* trails;
		void* trailElems;
		void* bolts;
		void* sparkClouds;
		void* sparkFountains;
		void* sparkFountainClusters;
		unsigned __int16* deferredElems;
		volatile int firstFreeElem;
		volatile int firstFreeTrailElem;
		volatile int firstFreeTrail;
		volatile int firstFreeBolt;
		volatile int firstFreeSparkCloud;
		volatile int firstFreeSparkFountain;
		volatile int firstFreeSparkFountainCluster;
		volatile int deferredElemCount;
		volatile int activeElemCount;
		volatile int activeTrailElemCount;
		volatile int activeTrailCount;
		volatile int activeBoltCount;
		volatile int activeSparkCloudCount;
		volatile int activeSparkFountainCount;
		volatile int activeSparkFountainClusterCount;
		volatile int gfxCloudCount;
		FxVisState* visState;
		FxVisState* visStateBufferRead;
		FxVisState* visStateBufferWrite;
		volatile int firstActiveEffect;
		volatile int firstNewEffect;
		volatile int firstFreeEffect;
		unsigned __int16 allEffectHandles[1024];
		volatile int activeSpotLightEffectCount;
		volatile int activeSpotLightElemCount;
		unsigned __int16 activeSpotLightEffectHandle;
		unsigned __int16 activeSpotLightElemHandle;
		__int16 activeSpotLightBoltDobj;
		volatile int iteratorCount;
		int msecNow;
		volatile int msecDraw;
		int frameCount;
		bool isInitialized;
		bool needsGarbageCollection;
		bool isArchiving;
		char localClientNum;
		unsigned int restartList[32];
		FxEffect** restartEffectsList;
		unsigned int restartCount;
		unsigned int pad1[14];
	};

	struct ClientEntSound
	{
		float origin[3];
		snd_alias_list_t* aliasList;
	};

	struct nodetype
	{
		nodetype* left;
		nodetype* right;
		nodetype* parent;
		int weight;
		int symbol;
	};

	struct huff_t
	{
		int blocNode;
		int blocPtrs;
		nodetype* tree;
		nodetype* loc[257];
		nodetype** freelist;
		nodetype nodeList[768];
		nodetype* nodePtrs[768];
	};

	struct huffman_t
	{
		huff_t compressDecompress;
	};

	enum FF_DIR
	{
		FFD_DEFAULT = 0x0,
		FFD_MOD_DIR = 0x1,
		FFD_USER_MAP = 0x2,
	};

	struct ASISTAGE
	{
		int(__stdcall* ASI_stream_open)(unsigned int, int(__stdcall*)(unsigned int, void*, int, int), unsigned int);
		int(__stdcall* ASI_stream_process)(int, void*, int);
		int(__stdcall* ASI_stream_seek)(int, int);
		int(__stdcall* ASI_stream_close)(int);
		int(__stdcall* ASI_stream_property)(int, unsigned int, void*, const void*, void*);
		unsigned int INPUT_BIT_RATE;
		unsigned int INPUT_SAMPLE_RATE;
		unsigned int INPUT_BITS;
		unsigned int INPUT_CHANNELS;
		unsigned int OUTPUT_BIT_RATE;
		unsigned int OUTPUT_SAMPLE_RATE;
		unsigned int OUTPUT_BITS;
		unsigned int OUTPUT_CHANNELS;
		unsigned int OUTPUT_RESERVOIR;
		unsigned int POSITION;
		unsigned int PERCENT_DONE;
		unsigned int MIN_INPUT_BLOCK_SIZE;
		unsigned int RAW_RATE;
		unsigned int RAW_BITS;
		unsigned int RAW_CHANNELS;
		unsigned int REQUESTED_RATE;
		unsigned int REQUESTED_BITS;
		unsigned int REQUESTED_CHANS;
		unsigned int STREAM_SEEK_POS;
		unsigned int DATA_START_OFFSET;
		unsigned int DATA_LEN;
		int stream;
	};

	struct _STREAM
	{
		int block_oriented;
		int using_ASI;
		ASISTAGE* ASI;
		void* samp;
		unsigned int fileh;
		char* bufs[3];
		unsigned int bufsizes[3];
		int reset_ASI[3];
		int reset_seek_pos[3];
		int bufstart[3];
		void* asyncs[3];
		int loadedbufstart[2];
		int loadedorder[2];
		int loadorder;
		int bufsize;
		int readsize;
		unsigned int buf1;
		int size1;
		unsigned int buf2;
		int size2;
		unsigned int buf3;
		int size3;
		unsigned int datarate;
		int filerate;
		int filetype;
		unsigned int fileflags;
		int totallen;
		int substart;
		int sublen;
		int subpadding;
		unsigned int blocksize;
		int padding;
		int padded;
		int loadedsome;
		unsigned int startpos;
		unsigned int totalread;
		unsigned int loopsleft;
		unsigned int error;
		int preload;
		unsigned int preloadpos;
		int noback;
		int alldone;
		int primeamount;
		int readatleast;
		int playcontrol;
		void(__stdcall* callback)(_STREAM*);
		int user_data[8];
		void* next;
		int autostreaming;
		int docallback;
	};

	enum SND_EQTYPE
	{
		SND_EQTYPE_FIRST = 0x0,
		SND_EQTYPE_LOWPASS = 0x0,
		SND_EQTYPE_HIGHPASS = 0x1,
		SND_EQTYPE_LOWSHELF = 0x2,
		SND_EQTYPE_HIGHSHELF = 0x3,
		SND_EQTYPE_BELL = 0x4,
		SND_EQTYPE_LAST = 0x4,
		SND_EQTYPE_COUNT = 0x5,
		SND_EQTYPE_INVALID = 0x5,
	};

	struct __declspec(align(4)) SndEqParams
	{
		SND_EQTYPE type;
		float gain;
		float freq;
		float q;
		bool enabled;
	};

	struct MssEqInfo
	{
		SndEqParams params[3][64];
	};

	struct MssFileHandle
	{
		unsigned int id;
		MssFileHandle* next;
		int handle;
		char fileName[128];
		unsigned int hashCode;
		int offset;
		int fileOffset;
		int fileLength;
	};

	struct __declspec(align(4)) MssStreamReadInfo
	{
		char path[256];
		int timeshift;
		float fraction;
		int startDelay;
		_STREAM* handle;
		bool readError;
	};

	struct MssLocal
	{
		struct _DIG_DRIVER* driver;
		struct _SAMPLE* handle_sample[40];
		_STREAM* handle_stream[12];
		bool voiceEqDisabled[52];
		MssEqInfo eq[2];
		float eqLerp;
		unsigned int eqFilter;
		int currentRoomtype;
		MssFileHandle fileHandle[12];
		MssFileHandle* freeFileHandle;
		bool isMultiChannel;
		float realVolume[12];
		int playbackRate[52];
		MssStreamReadInfo streamReadInfo[12];
	};

	struct WinVars_t
	{
		HINSTANCE__* reflib_library;
		int reflib_active;
		HWND__* hWnd;
		HINSTANCE__* hInstance;
		int activeApp;
		int isMinimized;
		int recenterMouse;
		HHOOK__* lowLevelKeyboardHook;
		unsigned int sysMsgTime;
	};

#pragma endregion

#ifndef IDA
}
#endif
