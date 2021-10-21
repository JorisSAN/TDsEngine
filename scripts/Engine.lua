project ("Engine")
	kind "StaticLib"

	includedirs {
		path.join(BX_DIR,   "include"),
		path.join(BIMG_DIR, "include"),
		path.join(BGFX_DIR, "include"),
		path.join(BGFX_DIR, "3rdparty"),
		path.join("../common"),
		path.join("../common/entry"),
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