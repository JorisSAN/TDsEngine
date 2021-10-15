project ("Engine")
	kind "StaticLib"

	includedirs {
		path.join(BX_DIR,   "include"),
		path.join(BIMG_DIR, "include"),
		path.join(BGFX_DIR, "include"),
		path.join(BGFX_DIR, "3rdparty"),
		path.join(BGFX_DIR, "examples/common"),
	}

	files {
		path.join("../Engine/*"),
	}

    links {
		"example-common",
		"bgfx",
		"bimg_decode",
		"bimg",
		"bx",
	}