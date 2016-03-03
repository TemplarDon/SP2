#include "SP2.h"

//Shader information.
void SP2::LoadShaderCodes()
{
	//Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.2f, 0.0f);

	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);

	//Enable back face culling
	glEnable(GL_CULL_FACE);

	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	//Shaders
	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");

	//Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Mapping variables to tell gpu what is what
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");

	for (size_t S = 0; S < numLights; S++)
	{
		std::string baseString = "lights[" + std::to_string(S);

		static vector<std::string> endings =
		{
			"].position_cameraspace",
			"].color",
			"].power",
			"].kC",
			"].kL",
			"].kQ",
			"].type",
			"].spotDirection",
			"].cosCutoff",
			"].cosInner",
			"].exponent"
		};

		vector<std::string>::iterator i = endings.begin();

		lightUniforms[S][UL_POSITION] = glGetUniformLocation(m_programID, (baseString + *i).c_str()); i++;
		lightUniforms[S][UL_COLOR] = glGetUniformLocation(m_programID, (baseString + *i).c_str()); i++;
		lightUniforms[S][UL_POWER] = glGetUniformLocation(m_programID, (baseString + *i).c_str()); i++;
		lightUniforms[S][UL_KC] = glGetUniformLocation(m_programID, (baseString + *i).c_str()); i++;
		lightUniforms[S][UL_KL] = glGetUniformLocation(m_programID, (baseString + *i).c_str()); i++;
		lightUniforms[S][UL_KQ] = glGetUniformLocation(m_programID, (baseString + *i).c_str()); i++;
		lightUniforms[S][UL_TYPE] = glGetUniformLocation(m_programID, (baseString + *i).c_str()); i++;
		lightUniforms[S][UL_SPOTDIRECTION] = glGetUniformLocation(m_programID, (baseString + *i).c_str()); i++;
		lightUniforms[S][UL_COSCUTOFF] = glGetUniformLocation(m_programID, (baseString + *i).c_str()); i++;
		lightUniforms[S][UL_COSINNER] = glGetUniformLocation(m_programID, (baseString + *i).c_str()); i++;
		lightUniforms[S][UL_EXPONENT] = glGetUniformLocation(m_programID, (baseString + *i).c_str());
	}

	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");

	//Get a handle for our "colorTexture" uniform
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

	//Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	glUseProgram(m_programID);
	glUniform1i(m_parameters[U_NUMLIGHTS], numLights);
}

//Light data information.
void SP2::LoadLights()
{
	setLightData(0,						//Light index.
		Light::LIGHT_SPOT,				//Light type.
		{ -60, 12, 0 },					//Light position.
		{ 1, 1, 1 },					//Light color.
		1,								//Light power.
		1.0f, 0.01f, 0.001f,			//Light attenuation values. (constant, linear, quadratic)
		45, 30,							//Spotlight cutoff / inner values in degrees.
		3.0f,							//Spotlight exponent.
		{ 0.2f, 1.0f, 0.2f }			//Spotlight direction.
	);

	setLightData(1,
		Light::LIGHT_SPOT,
		{ 0, 10, 0 },
		{ 0, 1, 1 },
		1,
		1.0f, 0.01f, 0.001f,
		45, 30,
		3.0f,
		{ -0.2f, 1.0f, -0.2f }
	);

	setLightData(2,
		Light::LIGHT_SPOT,
		{ 3, 10, 0 },
		{ 1, 0, 0 },
		1,
		1.0f, 0.01f, 0.001f,
		45, 30,
		3.0f,
		{ -0.2f, 1.0f, 0 }
	);
}

//Mesh data information.
void SP2::LoadMeshes()
{
	//Text
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//5.tga");


	//AXES
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);


	//LIGHTBALL
	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1));


	//SKYBOX
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1));
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//spaceground.tga");

	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1));
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//purplenebula_ft_hd.tga");

	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1));
	meshList[GEO_BACK]->textureID = LoadTGA("Image//purplenebula_bk_hd.tga");

	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1));
	meshList[GEO_TOP]->textureID = LoadTGA("Image//purplenebula_up_hd.tga");

	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1));
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//purplenebula_dn_hd.tga");

	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1));
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//purplenebula_lf_hd.tga");

	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1));
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//purplenebula_rt_hd.tga");


	//WALLS
	meshList[GEO_WALL] = MeshBuilder::GenerateOBJ("wall", "OBJ//TestWall2.obj");
	meshList[GEO_WALL]->textureID = LoadTGA("Image//TestWall.tga");

	meshList[GEO_WALL2] = MeshBuilder::GenerateOBJ("wall2", "OBJ//TestWall.obj");
	meshList[GEO_WALL2]->textureID = LoadTGA("Image//TestWall.tga");

	meshList[GEO_GATETOP] = MeshBuilder::GenerateOBJ("wall", "OBJ//TESTDOOR.obj");
	meshList[GEO_GATETOP]->textureID = LoadTGA("Image//gateTopUV.tga");

	meshList[GEO_GATETOP2] = MeshBuilder::GenerateOBJ("wall", "OBJ//TESTDOOR2.obj");
	meshList[GEO_GATETOP2]->textureID = LoadTGA("Image//gateTopUV.tga");

	meshList[GEO_GATE] = MeshBuilder::GenerateOBJ("wall", "OBJ//gate.obj");
	meshList[GEO_GATE]->textureID = LoadTGA("Image//gateUV.tga");


	//GROUND MESH
	meshList[GEO_GROUND] = MeshBuilder::GenerateQuad("ground", Color(1, 1, 1));
	meshList[GEO_GROUND]->textureID = LoadTGA("Image//castleFloor.tga");

	meshList[GEO_GROUND]->material.kAmbient.Set(0.15f, 0.15f, 0.15f);
	meshList[GEO_GROUND]->material.kDiffuse.Set(0.6, 0.6, 0.6);
	meshList[GEO_GROUND]->material.kSpecular.Set(0.4, 0.4, 0.4);
	meshList[GEO_GROUND]->material.kShininess = 1;


	//SCREEN
	//INVENTORY
	meshList[GEO_INVENTORY] = MeshBuilder::GenerateOBJ("Sofa", "OBJ//Inventory.obj");
	meshList[GEO_INVENTORY]->textureID = LoadTGA("Image//Inventory.tga");

	//HAND
	meshList[GEO_HAND] = MeshBuilder::GenerateOBJ("Sofa", "OBJ//Hand.obj");
	meshList[GEO_HAND]->textureID = LoadTGA("Image//Hand.tga");

	//SCREEN
	//INVENTORY
	meshList[GEO_FIRSTBOX] = MeshBuilder::GenerateOBJ("Sofa", "OBJ//BOX.obj");
	meshList[GEO_FIRSTBOX]->textureID = LoadTGA("Image//BOX1.tga");

	meshList[GEO_SECONDBOX] = MeshBuilder::GenerateOBJ("Sofa", "OBJ//BOX.obj");
	meshList[GEO_SECONDBOX]->textureID = LoadTGA("Image//BOX2.tga");

	meshList[GEO_THIRDBOX] = MeshBuilder::GenerateOBJ("Sofa", "OBJ//BOX.obj");
	meshList[GEO_THIRDBOX]->textureID = LoadTGA("Image//BOX3.tga");

	meshList[GEO_FOURTHBOX] = MeshBuilder::GenerateOBJ("Sofa", "OBJ//BOX.obj");
	meshList[GEO_FOURTHBOX]->textureID = LoadTGA("Image//BOX4.tga");

	meshList[GEO_FIFTHBOX] = MeshBuilder::GenerateOBJ("Sofa", "OBJ//BOX.obj");
	meshList[GEO_FIFTHBOX]->textureID = LoadTGA("Image//BOX5.tga");

	meshList[GEO_SIXTHBOX] = MeshBuilder::GenerateOBJ("Sofa", "OBJ//BOX.obj");
	meshList[GEO_SIXTHBOX]->textureID = LoadTGA("Image//BOX6.tga");


	//WEAPON
	//PICKAXE
	meshList[GEO_HOLDPICKAXE] = MeshBuilder::GenerateOBJ("Sofa", "OBJ//Pickaxe1.obj");
	meshList[GEO_HOLDPICKAXE]->textureID = LoadTGA("Image//Pickaxe1.tga");
	//GUN
	meshList[GEO_HOLDGUN] = MeshBuilder::GenerateOBJ("Sofa", "OBJ//NewGun.obj");
	meshList[GEO_HOLDGUN]->textureID = LoadTGA("Image//NewGun.tga");



	//POINTERS
	//INVENTORY
	meshList[GEO_POINTER] = MeshBuilder::GenerateOBJ("Sofa", "OBJ//Pointer.obj");
	meshList[GEO_POINTER]->textureID = LoadTGA("Image//Pointer.tga");
	//CAFE MENU
	meshList[GEO_CAFEPOINTER] = MeshBuilder::GenerateOBJ("Sofa", "OBJ//Pointer.obj");
	meshList[GEO_CAFEPOINTER]->textureID = LoadTGA("Image//Pointer.tga");



	//NPCS
	//SHOPKEEPER
	meshList[GEO_SHOPKEEPER] = MeshBuilder::GenerateOBJ("Speakers", "OBJ//Shopkeeper.obj");
	meshList[GEO_SHOPKEEPER]->textureID = LoadTGA("Image//Shopkeeper.tga");
	InteractableOBJs shopkeeper = InteractableOBJs("shopkeeper", meshList[GEO_SHOPKEEPER]->maxPos, meshList[GEO_SHOPKEEPER]->minPos, Position(220, 2, -10), 2, 0, Vector3(0, 0, 0));
	shopkeeper.setRequirements(27, 15);
	InteractablesList.push_back(shopkeeper);
	//NURSE
	meshList[GEO_NURSE] = MeshBuilder::GenerateOBJ("Sofa", "OBJ//Nurse.obj");
	meshList[GEO_NURSE]->textureID = LoadTGA("Image//Nurse.tga");
	InteractableOBJs nurse = InteractableOBJs("nurse", meshList[GEO_NURSE]->maxPos, meshList[GEO_NURSE]->minPos, Position(261, 2, -70), 2, 0, Vector3(0, 0, 0));
	nurse.setRequirements(30, 12);
	InteractablesList.push_back(nurse);
	//DOCTOR //250, 2, -100
	meshList[GEO_DOCTOR] = MeshBuilder::GenerateOBJ("Sofa", "OBJ//Doctor.obj");
	meshList[GEO_DOCTOR]->textureID = LoadTGA("Image//Doctor.tga");
	InteractableOBJs doctor = InteractableOBJs("doctor", meshList[GEO_DOCTOR]->maxPos, meshList[GEO_DOCTOR]->minPos, Position(232, 2, -130), 2, 0, Vector3(0, 0, 0));
	doctor.setRequirements(30, 12);
	InteractablesList.push_back(doctor);
	//TRADER
	meshList[GEO_TRADER] = MeshBuilder::GenerateOBJ("Sofa", "OBJ//Trader.obj");
	meshList[GEO_TRADER]->textureID = LoadTGA("Image//Trader.tga");
	InteractableOBJs trader = InteractableOBJs("trader", meshList[GEO_TRADER]->maxPos, meshList[GEO_TRADER]->minPos, Position(140, 2, 125), 2, 0, Vector3(0, 0, 0));
	trader.setRequirements(30, 12);
	InteractablesList.push_back(trader);
	//SOLDIER
	meshList[GEO_SOLDIER] = MeshBuilder::GenerateOBJ("Sofa", "OBJ//Soldier.obj");
	meshList[GEO_SOLDIER]->textureID = LoadTGA("Image//Soldier.tga");
	InteractableOBJs soldier = InteractableOBJs("soldier", meshList[GEO_SOLDIER]->maxPos, meshList[GEO_SOLDIER]->minPos, Position(148, 2, 200), 2, 0, Vector3(0, 0, 0));
	soldier.setRequirements(25, 15);
	InteractablesList.push_back(soldier);
	//CHEF
	meshList[GEO_CHEF] = MeshBuilder::GenerateOBJ("Speakers", "OBJ//Chef.obj");
	meshList[GEO_CHEF]->textureID = LoadTGA("Image//Chef.tga");
	InteractableOBJs chef = InteractableOBJs("chef", meshList[GEO_CHEF]->maxPos, meshList[GEO_CHEF]->minPos, Position(280, 2, -2), 2, 0, Vector3(0, 0, 0));
	chef.setRequirements(32, 15);
	InteractablesList.push_back(chef);
	//SPACEGUY
	meshList[GEO_SPACEGUY] = MeshBuilder::GenerateOBJ("Sofa", "OBJ//Spaceman.obj");
	meshList[GEO_SPACEGUY]->textureID = LoadTGA("Image//Spaceman.tga");
	InteractableOBJs spaceguy = InteractableOBJs("spaceguy", meshList[GEO_SPACEGUY]->maxPos, meshList[GEO_SPACEGUY]->minPos, Position(271, 1.8, 143), 2, 0, Vector3(0, 0, 0));
	spaceguy.setRequirements(25, 12);
	InteractablesList.push_back(spaceguy);

	InteractableOBJs spaceguy2 = InteractableOBJs("spaceguy2", meshList[GEO_SPACEGUY]->maxPos, meshList[GEO_SPACEGUY]->minPos, Position(105, 2.8, 5), 2, 0, Vector3(0, 0, 0));
	spaceguy2.setRequirements(25, 12);
	InteractablesList.push_back(spaceguy2);


	//TEXT BOX
	meshList[GEO_NPCDIALOGUEBOX] = MeshBuilder::GenerateOBJ("Sofa", "OBJ//NPCTextBox.obj");
	meshList[GEO_NPCDIALOGUEBOX]->textureID = LoadTGA("Image//NPCTextBox.tga");

	meshList[GEO_INSTRUCTIONBOX] = MeshBuilder::GenerateOBJ("Sofa", "OBJ//NPCTextBox.obj");
	meshList[GEO_INSTRUCTIONBOX]->textureID = LoadTGA("Image//Instructions.tga");



	//HEALTH BAR
	meshList[GEO_DEADHEALTHBAR] = MeshBuilder::GenerateOBJ("Sofa", "OBJ//HealthBar.obj");
	meshList[GEO_DEADHEALTHBAR]->textureID = LoadTGA("Image//DeadHealthBar.tga");

	meshList[GEO_ALIVEHEALTHBAR] = MeshBuilder::GenerateOBJ("Sofa", "OBJ//HealthBar.obj");
	meshList[GEO_ALIVEHEALTHBAR]->textureID = LoadTGA("Image//AliveHealthBar.tga");




	//CAFE
	initRoomTemplate(Position(250, 2, 30));
	//COUNTER
	meshList[GEO_COUNTER] = MeshBuilder::GenerateOBJ("Speakers", "OBJ//Counter.obj");
	meshList[GEO_COUNTER]->textureID = LoadTGA("Image//Counter.tga");
	InteractableOBJs counter = InteractableOBJs("counter", meshList[GEO_COUNTER]->maxPos, meshList[GEO_COUNTER]->minPos, Position(280, 2, 0), 3, 0, Vector3(0, 0, 0));
	counter.setRequirements(40, 15);
	InteractablesList.push_back(counter);
	//FRIDGE
	meshList[GEO_FRIDGE] = MeshBuilder::GenerateOBJ("Speakers", "OBJ//Fridge.obj");
	meshList[GEO_FRIDGE]->textureID = LoadTGA("Image//Fridge.tga");
	//TABLE
	meshList[GEO_TABLE] = MeshBuilder::GenerateOBJ("Speakers", "OBJ//Table.obj");
	meshList[GEO_TABLE]->textureID = LoadTGA("Image//Table.tga");
	InteractableOBJs table = InteractableOBJs("table", meshList[GEO_TABLE]->maxPos, meshList[GEO_TABLE]->minPos, Position(280, 2, 65), 4, 0, Vector3(0, 0, 0));
	table.setRequirements(25, 15);
	InteractablesList.push_back(table);
	//VENDING
	meshList[GEO_VENDING] = MeshBuilder::GenerateOBJ("Speakers", "OBJ//Vending.obj");
	meshList[GEO_VENDING]->textureID = LoadTGA("Image//Vending.tga");
	InteractableOBJs vending = InteractableOBJs("vending", meshList[GEO_VENDING]->maxPos, meshList[GEO_VENDING]->minPos, Position(210, 2, 88), 3, 0, Vector3(0, 0, 0));
	vending.setRequirements(52, 10);  //55, 15
	InteractablesList.push_back(vending);
	//TOKEN
	meshList[GEO_TOKEN] = MeshBuilder::GenerateOBJ("Speakers", "OBJ//Token.obj");
	meshList[GEO_TOKEN]->textureID = LoadTGA("Image//Token.tga");
	InteractableOBJs token = InteractableOBJs("token", meshList[GEO_TOKEN]->maxPos, meshList[GEO_TOKEN]->minPos, Position(276, TokenTranslate, 61), 2, 0, Vector3(0, 0, 0));
	token.setRequirements(30, 5);
	InteractablesList.push_back(token);
	//COKE
	meshList[GEO_COKE] = MeshBuilder::GenerateOBJ("Speakers", "OBJ//Coke.obj");
	meshList[GEO_COKE]->textureID = LoadTGA("Image//Coke.tga");
	//CAFE MENU TEXT BOX
	meshList[GEO_CAFETEXTBOX] = MeshBuilder::GenerateOBJ("Speakers", "OBJ//TextBoxCafeMenu.obj");
	meshList[GEO_CAFETEXTBOX]->textureID = LoadTGA("Image//CafeMenu.tga");
	//BREAD
	meshList[GEO_BREAD] = MeshBuilder::GenerateOBJ("Speakers", "OBJ//Bread.obj");
	meshList[GEO_BREAD]->textureID = LoadTGA("Image//Bread.tga");
	//COFFEE
	meshList[GEO_COFFEE] = MeshBuilder::GenerateOBJ("Speakers", "OBJ//Coffee.obj");
	meshList[GEO_COFFEE]->textureID = LoadTGA("Image//Coffee.tga");
	//APPLE
	meshList[GEO_APPLE] = MeshBuilder::GenerateOBJ("Speakers", "OBJ//Apple.obj");
	meshList[GEO_APPLE]->textureID = LoadTGA("Image//Apple.tga");










	//SHOP LIST
	meshList[GEO_SHOPLIST1] = MeshBuilder::GenerateOBJ("Speakers", "OBJ//TextBoxCafeMenu.obj");
	meshList[GEO_SHOPLIST1]->textureID = LoadTGA("Image//ShopList1.tga");

	meshList[GEO_SHOPLIST2] = MeshBuilder::GenerateOBJ("Speakers", "OBJ//TextBoxCafeMenu.obj");
	meshList[GEO_SHOPLIST2]->textureID = LoadTGA("Image//ShopList2.tga");

	meshList[GEO_SHOPLIST3] = MeshBuilder::GenerateOBJ("Speakers", "OBJ//TextBoxCafeMenu.obj");
	meshList[GEO_SHOPLIST3]->textureID = LoadTGA("Image//ShopList3.tga");

	meshList[GEO_SHOPLIST4] = MeshBuilder::GenerateOBJ("Speakers", "OBJ//TextBoxCafeMenu.obj");
	meshList[GEO_SHOPLIST4]->textureID = LoadTGA("Image//ShopList4.tga");

	//SHOP LIST POINTER
	meshList[GEO_SHOPPOINTER1] = MeshBuilder::GenerateOBJ("Sofa", "OBJ//Pointer.obj");
	meshList[GEO_SHOPPOINTER1]->textureID = LoadTGA("Image//Pointer2.tga");




	//RECREATIOMAL ROOM
	initRoomTemplate(Position(120, 2, 30));
	//SPEAKERS
	meshList[GEO_SPEAKERS] = MeshBuilder::GenerateOBJ("Speakers", "OBJ//RecRoomSpeakers.obj");
	meshList[GEO_SPEAKERS]->textureID = LoadTGA("Image//RecRoomSpeakers.tga");
	//SOFA
	meshList[GEO_SOFA] = MeshBuilder::GenerateOBJ("Sofa", "OBJ//sofa.obj");
	meshList[GEO_SOFA]->textureID = LoadTGA("Image//sofa.tga");



	//BUNK ROOM
	initRoomTemplate(Position(250, 2, 160));
	//BUNK
	meshList[GEO_BUNK] = MeshBuilder::GenerateOBJ("Sofa", "OBJ//Bunk.obj");
	meshList[GEO_BUNK]->textureID = LoadTGA("Image//Bunk.tga");
	InteractableOBJs bunk = InteractableOBJs("bunk", meshList[GEO_BUNK]->maxPos, meshList[GEO_BUNK]->minPos, Position(288, 3, 127), 2, 0, Vector3(0, 0, 0));
	InteractableOBJs bunk2 = InteractableOBJs("bunk", meshList[GEO_BUNK]->maxPos, meshList[GEO_BUNK]->minPos, Position(271, 3, 127), 2, 0, Vector3(0, 0, 0));
	InteractableOBJs bunk3 = InteractableOBJs("bunk", meshList[GEO_BUNK]->maxPos, meshList[GEO_BUNK]->minPos, Position(210, 3, 127), 2, 0, Vector3(0, 0, 0));
	InteractableOBJs bunk4 = InteractableOBJs("bunk", meshList[GEO_BUNK]->maxPos, meshList[GEO_BUNK]->minPos, Position(227, 3, 127), 2, 0, Vector3(0, 0, 0));
	InteractableOBJs bunk5 = InteractableOBJs("bunk", meshList[GEO_BUNK]->maxPos, meshList[GEO_BUNK]->minPos, Position(288, 3, 191.5), 2, 0, Vector3(0, 0, 0));
	InteractableOBJs bunk6 = InteractableOBJs("bunk", meshList[GEO_BUNK]->maxPos, meshList[GEO_BUNK]->minPos, Position(271, 3, 191.5), 2, 0, Vector3(0, 0, 0));
	InteractablesList.push_back(bunk);
	InteractablesList.push_back(bunk2);
	InteractablesList.push_back(bunk3);
	InteractablesList.push_back(bunk4);
	InteractablesList.push_back(bunk5);
	InteractablesList.push_back(bunk6);
	//SPACESUIT
	meshList[GEO_SPACESUIT] = MeshBuilder::GenerateOBJ("Sofa", "OBJ//Spacesuit.obj");
	meshList[GEO_SPACESUIT]->textureID = LoadTGA("Image//Spacesuit.tga");
	InteractableOBJs spacesuit = InteractableOBJs("spacesuit", meshList[GEO_SPACESUIT]->maxPos, meshList[GEO_SPACESUIT]->minPos, Position(220, SuitTranslate, 190), 2, 0, Vector3(0, 0, 0));
	spacesuit.setRequirements(25, 15);
	InteractablesList.push_back(spacesuit);
	//SPACE MASK
	meshList[GEO_SPACEMASK] = MeshBuilder::GenerateOBJ("Sofa", "OBJ//Spacemask.obj");
	meshList[GEO_SPACEMASK]->textureID = LoadTGA("Image//Spacemask.tga");
	//WINDOW
	meshList[GEO_WINDOW] = MeshBuilder::GenerateOBJ("Sofa", "OBJ//Window.obj");
	meshList[GEO_WINDOW]->textureID = LoadTGA("Image//Window.tga");
	//HUD
	meshList[GEO_HUD] = MeshBuilder::GenerateOBJ("Sofa", "OBJ//HUD.obj");
	meshList[GEO_HUD]->textureID = LoadTGA("Image//HUD.tga");



	//INFIRMARY ROOM
	initRoomTemplate(Position(250, 2, -100));
	//HEALING TUBE
	meshList[GEO_HEALING_TUBE] = MeshBuilder::GenerateOBJ("healing tube", "OBJ//Infirmary Models//healingTube.obj");
	meshList[GEO_HEALING_TUBE]->textureID = LoadTGA("Image//Infirmary Textures//healingTubeUV.tga");
	InteractableOBJs healingTube = InteractableOBJs("healing tube", meshList[GEO_HEALING_TUBE]->maxPos, meshList[GEO_HEALING_TUBE]->minPos, Position(250 - 30, 2 + 15, -100 - 30), 5, 0, Vector3(0, 0, 0));
	healingTube.setRequirements(25, 15);
	InteractablesList.push_back(healingTube);
	//BED
	meshList[GEO_BED] = MeshBuilder::GenerateOBJ("hospital bed", "OBJ//Infirmary Models//hospitalBed.obj");
	meshList[GEO_BED]->textureID = LoadTGA("Image//Infirmary Textures//hospitalBedUV.tga");
	InteractableOBJs bed1 = InteractableOBJs("hospital bed 1", meshList[GEO_BED]->maxPos, meshList[GEO_BED]->minPos, Position(250 + 40, 2, -100 + 30), 5, 0, Vector3(0, 0, 0));
	bed1.setRequirements(25, 15);
	InteractablesList.push_back(bed1);
	InteractableOBJs bed2 = InteractableOBJs("hospital bed 2", meshList[GEO_BED]->maxPos, meshList[GEO_BED]->minPos, Position(250 + 20, 2, -100 + 30), 5, 0, Vector3(0, 0, 0));
	bed2.setRequirements(25, 15);
	InteractablesList.push_back(bed2);
	InteractableOBJs bed3 = InteractableOBJs("hospital bed 3", meshList[GEO_BED]->maxPos, meshList[GEO_BED]->minPos, Position(250 - 40, 2, -100 + 30), 5, 0, Vector3(0, 0, 0));
	bed3.setRequirements(25, 15);
	InteractablesList.push_back(bed3);
	InteractableOBJs bed4 = InteractableOBJs("hospital bed 4", meshList[GEO_BED]->maxPos, meshList[GEO_BED]->minPos, Position(250 - 20, 2, -100 + 30), 5, 0, Vector3(0, 0, 0));
	bed4.setRequirements(25, 15);
	InteractablesList.push_back(bed4);
	InteractableOBJs bed5 = InteractableOBJs("hospital bed5", meshList[GEO_BED]->maxPos, meshList[GEO_BED]->minPos, Position(250 + 40, 2, -100 - 30), 5, 0, Vector3(0, 0, 0));
	bed5.setRequirements(25, 15);
	InteractablesList.push_back(bed5);
	InteractableOBJs bed6 = InteractableOBJs("hospital bed 6", meshList[GEO_BED]->maxPos, meshList[GEO_BED]->minPos, Position(250 + 20, 2, -100 - 30), 5, 0, Vector3(0, 0, 0));
	bed6.setRequirements(25, 15);
	InteractablesList.push_back(bed6);



	//ARMOURY // SHOP
	initRoomTemplate(Position(120, 2, 160));
	//GUN
	meshList[GEO_GUN] = MeshBuilder::GenerateOBJ("gun", "OBJ//Armoury Models//gun.obj");
	meshList[GEO_GUN]->textureID = LoadTGA("Image//Armoury Textures//gunUV.tga");
	InteractableOBJs gun = InteractableOBJs("gun", meshList[GEO_GUN]->maxPos, meshList[GEO_GUN]->minPos, Position(120 + 40, 2, 160 + 40), 1, 0, Vector3(0, 0, 0));
	gun.setRequirements(25, 15);
	InteractablesList.push_back(gun);
	//GUN RACK
	meshList[GEO_GUN_RACK] = MeshBuilder::GenerateOBJ("gun rack", "OBJ//Armoury Models//gunrack.obj");
	meshList[GEO_GUN_RACK]->textureID = LoadTGA("Image//Armoury Textures//gunrackUV.tga");
	InteractableOBJs gunRack = InteractableOBJs("gun rack", meshList[GEO_GUN_RACK]->maxPos, meshList[GEO_GUN_RACK]->minPos, Position(120 + 40, 2, 160 + 40), 6, 0, Vector3(0, 0, 0));
	gunRack.setRequirements(25, 15);
	InteractablesList.push_back(gunRack);
	//SHOOTING RANGE
	meshList[GEO_SHOOTING_RANGE] = MeshBuilder::GenerateOBJ("shooting range", "OBJ//Armoury Models//shootingRange.obj");
	meshList[GEO_SHOOTING_RANGE]->textureID = LoadTGA("Image//Armoury Textures//shootingRangeUV.tga");
	InteractableOBJs shootingRange = InteractableOBJs("shooting range", meshList[GEO_SHOOTING_RANGE]->maxPos, meshList[GEO_SHOOTING_RANGE]->minPos, Position(120 + 5, 2, 160 + 40), 6, 0, Vector3(0, 0, 0));
	shootingRange.setRequirements(25, 15);
	InteractablesList.push_back(shootingRange);
	//TARGET DUMMY
	meshList[GEO_TARGET] = MeshBuilder::GenerateOBJ("target dummy", "OBJ//Armoury Models//target.obj");
	meshList[GEO_TARGET]->textureID = LoadTGA("Image//Armoury Textures//targetUV.tga");
	InteractableOBJs target = InteractableOBJs("target dummy", meshList[GEO_TARGET]->maxPos, meshList[GEO_TARGET]->minPos, Position(120 - 35, 17, 160 + 38), 7, 0, Vector3(0, 0, 0));
	target.setRequirements(50, 10);
	InteractablesList.push_back(target);
	//SHOP
	meshList[GEO_SHOP] = MeshBuilder::GenerateOBJ("shop", "OBJ//shop.obj");
	meshList[GEO_SHOP]->textureID = LoadTGA("Image//shopUV.tga");
	InteractableOBJs shop = InteractableOBJs("shop", meshList[GEO_SHOP]->maxPos, meshList[GEO_SHOP]->minPos, Position(120 + 30, 2, 160 - 35), 12, 0, Vector3(0, 0, 0));
	shop.setRequirements(50, 20);
	InteractablesList.push_back(shop);


	//SCIENCE LAB (GARY'S)
	initRoomTemplate(Position(120, 2, -100));
	//TABLE
	meshList[GEO_SCIENCELAB_TABLE] = MeshBuilder::GenerateOBJ("sciencelab_beaker", "OBJ//ScienceLab//table.obj");
	meshList[GEO_SCIENCELAB_TABLE]->textureID = LoadTGA("Image//ScienceLab//table_uv.tga");
	//CUPBOARD
	meshList[GEO_SCIENCELAB_CUPBOARD] = MeshBuilder::GenerateOBJ("sciencelab_cupboard", "OBJ//ScienceLab//cupboard.obj");
	meshList[GEO_SCIENCELAB_CUPBOARD]->textureID = LoadTGA("Image//ScienceLab//cupboard_uv.tga");
	//BEAKER
	meshList[GEO_SCIENCELAB_BEAKER] = MeshBuilder::GenerateOBJ("sciencelab_beaker", "OBJ//ScienceLab//beaker.obj");
	meshList[GEO_SCIENCELAB_BEAKER]->textureID = LoadTGA("Image//ScienceLab//beaker_uv.tga");

	//Keypad + Safe (Gary Goh's)

	meshList[GEO_KEYPAD] = MeshBuilder::GenerateOBJ("kaypad", "OBJ//keypad.obj");
	meshList[GEO_KEYPAD]->textureID = LoadTGA("Image//keypad_uv.tga");

	meshList[GEO_SAFE_BOX] = MeshBuilder::GenerateOBJ("safe_box", "OBJ//safe_box.obj");
	meshList[GEO_SAFE_BOX]->textureID = LoadTGA("Image//safe_box_UV.tga");

	meshList[GEO_SAFE_DOOR] = MeshBuilder::GenerateOBJ("safe_door", "OBJ//safe_door.obj");
	meshList[GEO_SAFE_DOOR]->textureID = LoadTGA("Image//safe_door_UV.tga");

	//MINING (BECKHAM'S)
	//TRADE POST
	meshList[GEO_TRADEPOST] = MeshBuilder::GenerateOBJ("Tradepost", "OBJ//TradingPost.obj");
	meshList[GEO_TRADEPOST]->textureID = LoadTGA("Image//TradingPostTexture2.tga");

	//CRYSTAL
	meshList[GEO_CRYSTAL] = MeshBuilder::GenerateOBJ("Crystal", "OBJ//crystal2.obj");
	meshList[GEO_CRYSTAL]->textureID = LoadTGA("Image//crystal_Tile.tga");

	meshList[GEO_BASE] = MeshBuilder::GenerateOBJ("base", "OBJ//base.obj");
	meshList[GEO_BASE]->textureID = LoadTGA("Image//baseUV.tga");

	//ASTEROIDS   
	meshList[GEO_ASTEROID] = MeshBuilder::GenerateOBJ("asteroid", "OBJ//Rock1.obj");
	meshList[GEO_ASTEROID]->textureID = LoadTGA("Image//Asteroid.tga");

	//HANGAR
	initSpaceShip();
	// Helipad (Ship Spawn)
	meshList[GEO_HELIPAD] = MeshBuilder::GenerateOBJ("helipad", "OBJ//helipad.obj");
	meshList[GEO_HELIPAD]->textureID = LoadTGA("Image//helipadUV.tga");
	InteractableOBJs helipad = InteractableOBJs("helipad", meshList[GEO_HELIPAD]->maxPos, meshList[GEO_HELIPAD]->minPos, Position(shipStartingPos.x, shipStartingPos.y - 15, shipStartingPos.z), 1, 0, Vector3(0, 0, 0));
	helipad.setRequirements(25, 15);
	InteractablesList.push_back(helipad);


	//HELIPADSIGN
	meshList[GEO_HELIPADSIGN] = MeshBuilder::GenerateOBJ("helipad", "OBJ//HelipadSignBoard.obj");
	meshList[GEO_HELIPADSIGN]->textureID = LoadTGA("Image//HelipadSignBoard.tga");










	// Base
	meshList[GEO_BASE] = MeshBuilder::GenerateOBJ("base", "OBJ//base.obj");
	meshList[GEO_BASE]->textureID = LoadTGA("Image//baseUV.tga");
	InteractableOBJs base1 = InteractableOBJs("base1", meshList[GEO_BASE]->maxPos, meshList[GEO_BASE]->minPos, Position(250, 62, -80), 40, 0, Vector3(0, 0, 0)); //83, 25, 82
	base1.setRequirements(25, 15);
	InteractablesList.push_back(base1);

	InteractableOBJs base2 = InteractableOBJs("base2", meshList[GEO_BASE]->maxPos, meshList[GEO_BASE]->minPos, Position(120, 62, -80), 40, 0, Vector3(0, 0, 0)); //83, 25, 82
	base2.setRequirements(25, 15);
	InteractablesList.push_back(base2);

	InteractableOBJs base3 = InteractableOBJs("base3", meshList[GEO_BASE]->maxPos, meshList[GEO_BASE]->minPos, Position(120, 62, 120), 40, 0, Vector3(0, 0, 0)); //83, 25, 82
	base3.setRequirements(25, 15);
	InteractablesList.push_back(base3);

	InteractableOBJs base4 = InteractableOBJs("base4", meshList[GEO_BASE]->maxPos, meshList[GEO_BASE]->minPos, Position(250, 62, 120), 40, 0, Vector3(0, 0, 0)); //83, 25, 82
	base4.setRequirements(25, 15);
	InteractablesList.push_back(base4);

	// MAZE 
	initMaze();

	// Mountains (For Boundary)
	initMountains();

}

//Sets the lights' data (for initialization purposes).
void SP2::setLightData(
	const size_t &index,
	const Light::LIGHT_TYPE &type,
	const Position &pos,
	const Color &color,
	const float &power,
	const float &kC,
	const float &kL,
	const float &kQ,
	const float &cutoff,
	const float &inner,
	const float &exponent,
	const Vector3 &spotDirection)
{
	if (index >= numLights) return;

	light[index].type = type;
	light[index].position = pos;
	light[index].color = color;
	light[index].power = power;
	light[index].kC = kC;
	light[index].kL = kL;
	light[index].kQ = kQ;
	light[index].cosCutoff = cos(Math::DegreeToRadian(cutoff));
	light[index].cosInner = cos(Math::DegreeToRadian(inner));
	light[index].exponent = exponent;
	light[index].spotDirection = spotDirection;

	glUniform1i(lightUniforms[index][UL_TYPE], light[index].type);
	glUniform3fv(lightUniforms[index][UL_COLOR], 1, &light[index].color.r);
	glUniform1f(lightUniforms[index][UL_POWER], light[index].power);
	glUniform1f(lightUniforms[index][UL_KC], light[index].kC);
	glUniform1f(lightUniforms[index][UL_KL], light[index].kL);
	glUniform1f(lightUniforms[index][UL_KQ], light[index].kQ);
	glUniform1f(lightUniforms[index][UL_COSCUTOFF], light[index].cosCutoff);
	glUniform1f(lightUniforms[index][UL_COSINNER], light[index].cosInner);
	glUniform1f(lightUniforms[index][UL_EXPONENT], light[index].exponent);
}

//Sets the light's color.
void SP2::setLightColor(const size_t &index, const Color &C)
{
	if (index >= numLights) return;

	light[index].color = C;
	glUniform3fv(lightUniforms[index][UL_COLOR], 1, &light[index].color.r);
}

//Sets the light's power.
void SP2::setLightPower(const size_t &index, const float &P)
{
	if (index >= numLights) return;

	light[index].power = P;
	glUniform1f(lightUniforms[index][UL_POWER], light[index].power);
}

//Moves the light's position.
void SP2::moveLightPosition(const size_t &index, const Vector3 &M)
{
	if (index >= numLights) return;

	Position *p = &light[index].position;
	p->x += M.x;
	p->y += M.y;
	p->z += M.z;
}

//Rotates the spotlight along the axis.
void SP2::rotateSpotlight(const size_t &index, const float &degrees, const Vector3 &axis)
{
	if (index >= numLights) return;
	if (light[index].type != Light::LIGHT_SPOT) return;

	Mtx44 rotation;
	rotation.SetToRotation(degrees, axis.x, axis.y, axis.z);

	Vector3 &d = light[index].spotDirection;

	d = rotation * d;
}

void SP2::initSpaceShip()
{
	// Space Ship
	meshList[GEO_SHIP] = MeshBuilder::GenerateOBJ("ship", "OBJ//V_Art Spaceship.obj");
	Ship someShip = Ship("ship", meshList[GEO_SHIP]->maxPos, meshList[GEO_SHIP]->minPos, shipStartingPos, 4, 0, Vector3(0, 0, 0), camPointer->target);
	someShip.setRequirements(50, 500);

	shipTemplatePtr = &someShip;
}

//Main rendering code
void SP2::RenderCode()
{

	//RENDER LIGHTBALL
	modelStack.PushMatrix();
	modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false, toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(thirdPersonCamera.GetFocusPoint()->x, thirdPersonCamera.GetFocusPoint()->y, thirdPersonCamera.GetFocusPoint()->z);
	RenderMesh(meshList[GEO_LIGHTBALL], false, toggleLight);
	modelStack.PopMatrix();

	//Debug for the Interactables list. 
	for (vector<InteractableOBJs>::iterator i = InteractablesList.begin(); i < InteractablesList.end(); i++)
	{
		if (i->name != "keypadButton1") continue;
		modelStack.PushMatrix();
		modelStack.Translate(i->pos.x, i->pos.y, i->pos.z);
		float s = i->getRequiredFocus();
		modelStack.Scale(s, s, s);
		RenderMesh(meshList[GEO_LIGHTBALL], false, toggleLight);
		modelStack.PopMatrix();
	}

	if (isInViewSpheres)
	{
		Position P = { firstPersonCamera.position.x, firstPersonCamera.position.y, firstPersonCamera.position.z };
		Vector3 V = firstPersonCamera.target - firstPersonCamera.position;

		for (vector<InteractableOBJs>::iterator i = InteractablesList.begin(); i < InteractablesList.end(); i++)
		{
			if (!i->isInView(P, V)) continue;
			modelStack.PushMatrix();
			modelStack.Translate(i->pos.x, i->pos.y, i->pos.z);
			float s = i->getRequiredFocus();
			modelStack.Scale(s, s, s);
			RenderMesh(meshList[GEO_LIGHTBALL], false, toggleLight);
			modelStack.PopMatrix();
		}
	}


	for (vector<Keypad>::iterator i = keypads.begin(); i < keypads.end(); i++)
	{
		modelStack.PushMatrix();
		{
			modelStack.Translate(i->pos.x, i->pos.y, i->pos.z);
			modelStack.Rotate(i->orientation, 0, 1, 0);
			modelStack.Scale(4.2f, 4.2f, 4.2f);
			RenderMesh(meshList[GEO_KEYPAD], true, toggleLight);
		}
		modelStack.PopMatrix();
	}

	modelStack.PushMatrix();
	{
		static float a = 0, b = 0, c = 0;

		const float d = 1.0f / 16.0f;

		if (Application::IsKeyPressed(VK_NUMPAD1)) a -= d;
		if (Application::IsKeyPressed(VK_NUMPAD4)) a += d;
		if (Application::IsKeyPressed(VK_NUMPAD2)) b -= d;
		if (Application::IsKeyPressed(VK_NUMPAD5)) b += d;
		if (Application::IsKeyPressed(VK_NUMPAD3)) c -= d;
		if (Application::IsKeyPressed(VK_NUMPAD6)) c += d;

		if (Application::IsKeyPressed(VK_NUMPAD0))
		{
			float DEBUG = 0;
		}

		modelStack.Translate(86.5f, 16, -148);
		modelStack.Scale(4.2f, 4.2f, 4.2f);
		RenderMesh(meshList[GEO_SAFE_BOX], false, toggleLight);
		modelStack.PushMatrix();
		{
			modelStack.Translate(-1.8f, 0, 1);
			modelStack.Rotate(safeDoorRotation, 0, -1, 0);
			RenderMesh(meshList[GEO_SAFE_DOOR], false, toggleLight);
			modelStack.Translate(1.8f, 0, 0.2f);
			RenderMesh(meshList[GEO_KEYPAD], false, toggleLight);
		}
		modelStack.PopMatrix();
	}
	modelStack.PopMatrix();

	if (ShipList.size() > 0 && shipBuilt == true)
	{
		modelStack.PushMatrix();
		RenderSpaceShip();
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(shipPos.x, shipPos.y, shipPos.z);
		modelStack.Scale(6, 6, 6);
		RenderMesh(meshList[GEO_LIGHTBALL], false, toggleLight);
		modelStack.PopMatrix();
	}


	//RENDER SKYBOX
	RenderSkybox();

	//RENDER CAFE
	RenderCafeRoom();

	//RENDER BUNK
	RenderBunkRoom();

	//RENDER SCIENCE LAB
	RenderScienceLab();

	//RENDER RECREATIONAL ROOM   
	RenderRecRoom();

	//RENDER RANDOM CRYSTAL GENERATION   
	RenderCrystals();

	//RENDER RANDOM ASTEROID GENERATION  
	RenderAsteroids();
	// Render Maze
	renderMaze();

	// Render Mountains
	modelStack.PushMatrix();
	renderMountains();
	modelStack.PopMatrix();

	// Base Top
	// Infirmary
	modelStack.PushMatrix();
	modelStack.Translate(250, 62, -80);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_BASE], false, toggleLight);
	modelStack.PopMatrix();

	// Sciene Lab
	modelStack.PushMatrix();
	modelStack.Translate(120, 62, -80);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_BASE], false, toggleLight);
	modelStack.PopMatrix();

	// Rec Room & Shop
	modelStack.PushMatrix();
	modelStack.Translate(120, 62, 120);
	modelStack.Rotate(0, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_BASE], false, toggleLight);
	modelStack.PopMatrix();

	// Bunks & Cafe
	modelStack.PushMatrix();
	modelStack.Translate(250, 62, 120);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_BASE], false, toggleLight);
	modelStack.PopMatrix();


	//GROUND MESH
	modelStack.PushMatrix();
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_QUAD], true, toggleLight);
	modelStack.PopMatrix();


	//RENDER ROOM TEMPLATES

	RenderRoomTemplate(Position(250, 2, 160));

	RenderRoomTemplate(Position(250, 2, 30));  //CAFE ROOM

	RenderRoomTemplate(Position(120, 2, 30));

	RenderRoomTemplate(Position(120, 2, -100));


	//INFIRMARY
	modelStack.PushMatrix();
	RenderRoomTemplate(Position(250, 2, -100));
	modelStack.Translate(250, 2, -100);
	RenderInfirmary();
	modelStack.PopMatrix();

	//ARMOURY / SHOP
	modelStack.PushMatrix();
	RenderRoomTemplate(Position(120, 2, 160));
	modelStack.Translate(120, 2, 160);
	RenderArmouryAndShop();
	modelStack.PopMatrix();

	//Keypad
	for (vector<Keypad>::iterator i = keypads.begin(); i < keypads.end(); i++)
	{
		modelStack.PushMatrix();
		{
			modelStack.Translate(i->pos.x, i->pos.y + 15, i->pos.z);
			modelStack.Rotate(i->orientation, 0, 1, 0);
			modelStack.Scale(4.2f, 4.2f, 4.2f);
			RenderMesh(meshList[GEO_KEYPAD], true, toggleLight);
		}
		modelStack.PopMatrix();
	}

	//INTERACTION

	// Helipad
	modelStack.PushMatrix();
	modelStack.Translate(shipStartingPos.x, shipStartingPos.y - 15, shipStartingPos.z);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_HELIPAD], true, toggleLight);
	modelStack.PopMatrix();



	//HELIPAD SIGN BOARD
	modelStack.PushMatrix();
	modelStack.Translate(370, 2, -75);
	/*modelStack.Rotate(180, 1, 0, 0);*/
	modelStack.Scale(2.2, 2.2, 2.2);
	RenderMesh(meshList[GEO_HELIPADSIGN], false, toggleLight);
	modelStack.PopMatrix();




	//APPLE
	if (AppleAppear == true)
	{
		RenderApple();
	}

	//COFFEE
	if (CoffeeAppear == true)
	{
		RenderCoffee();
	}

	//BREAD
	if (BreadAppear == true)
	{
		RenderBread();
	}


	//Note from Gary Goh: It's best to render the sprites first then the text.

	if (TokenOnScreen == true)
	{
		RenderTokenOnScreen(meshList[GEO_TOKEN], 5, 8, 6);
	}


	//PICK UP COKE
	if (RenderCoke == true)
	{
		RenderCokeOnScreen(meshList[GEO_COKE], 5, 8, 6);
	}



	if (DisplayCafeMenu == true)  //true
	{
		//DisplayInventory = true;
		RenderCafeTextboxOnScreen(meshList[GEO_CAFETEXTBOX], 5, 8, 6);

		RenderCafePointerOnScreen(meshList[GEO_CAFEPOINTER], 0.6, 44, cafeMenuPointer);     //62, 50, 38t
	}


	//DO NOT DELETE SHOP LIST STUFF
	if (DisplayShopList == true)   //true
	{
		RenderShopTextboxOnScreen(meshList[GEO_SHOPLIST1], 5, 8, 6);
		RenderShopPointerOnScreen(meshList[GEO_SHOPPOINTER1], 0.6, 44, shopListPointer);     //62, 50, 38t
	}

	if (DisplayShopList2 == true)
	{
		RenderShopTextboxOnScreen(meshList[GEO_SHOPLIST2], 5, 8, 6);
		RenderShopPointerOnScreen(meshList[GEO_SHOPPOINTER1], 0.6, 44, shopListPointer);     //62, 50, 38t
	}


	if (DisplayShopList3 == true)
	{
		RenderShopTextboxOnScreen(meshList[GEO_SHOPLIST3], 5, 8, 6);
		RenderShopPointerOnScreen(meshList[GEO_SHOPPOINTER1], 0.6, 44, shopListPointer);     //62, 50, 38t
	}

	if (DisplayShopList4 == true)
	{
		RenderShopTextboxOnScreen(meshList[GEO_SHOPLIST4], 5, 8, 6);
		RenderShopPointerOnScreen(meshList[GEO_SHOPPOINTER1], 0.6, 44, shopListPointer);     //62, 50, 38t
	}







	//INVENTORY & HANDS
	if (DisplayInventory == false)
	{
		//Inventory
		RenderInventoryOnScreen(meshList[GEO_FIRSTBOX], 5, 4.7, 2);
		RenderInventoryOnScreen(meshList[GEO_SECONDBOX], 5, 5.8, 2);
		RenderInventoryOnScreen(meshList[GEO_THIRDBOX], 5, 6.9, 2);
		RenderInventoryOnScreen(meshList[GEO_FOURTHBOX], 5, 8, 2);
		RenderInventoryOnScreen(meshList[GEO_FIFTHBOX], 5, 10.2, 2);
		RenderInventoryOnScreen(meshList[GEO_SIXTHBOX], 5, 11.3, 2);

		//POINTER
		RenderPointerOnScreen(meshList[GEO_POINTER], 0.4, translatePointer, 37);     //127, 141

        //Weapon 
        std::ostringstream weapon;
        weapon.str("");
        if (somePlayer.checkWeapon()) { weapon << "Equipped"; }
        else { weapon << "Unequipped"; }
        RenderTextOnScreen(meshList[GEO_TEXT], weapon.str(), Color(1, 0, 0), 1.3, 36, 4);

        //CRYSTAL COUNTS
        std::ostringstream as;
        as.str("");
        as << somePlayer.getCrystals();
        RenderTextOnScreen(meshList[GEO_TEXT], as.str(), Color(1, 0, 0), 2, 10.5, 2);

        // Ship Parts
        std::ostringstream engineText;
        engineText.str("");

        std::ostringstream wingsText;
        wingsText.str("");

        std::ostringstream hullText;
        hullText.str("");


        if (somePlayer.getParts().size() > 0)
        {
            for (list<ShipParts*>::iterator it = somePlayer.getParts().begin(); it != somePlayer.getParts().end(); ++it)
            {
                if ((*it)->getName() == "LightHull") { hullText << "Light"; }
                if ((*it)->getName() == "MediumHull") { hullText << "Medium"; }
                if ((*it)->getName() == "LargeHull") { hullText << "Large"; }

                if ((*it)->getName() == "DualWings") { wingsText << "Dual"; }
                if ((*it)->getName() == "QuadWings") { wingsText << "Quad"; }

                if ((*it)->getName() == "G1Engine") { engineText << "G1"; }
                if ((*it)->getName() == "G2Engine") { engineText << "G2"; }

            }
        }

        RenderTextOnScreen(meshList[GEO_TEXT], engineText.str(), Color(1, 0, 0), 2, 13, 2);

        RenderTextOnScreen(meshList[GEO_TEXT], wingsText.str(), Color(1, 0, 0), 2, 16, 2);

        RenderTextOnScreen(meshList[GEO_TEXT], hullText.str(), Color(1, 0, 0), 2, 19, 2);

	}

	if (HandDisappear == false)  //false
	{
		//Hand 1
		RenderHandOnScreen(meshList[GEO_HAND], 5, 0.8, 1);

		//Hand 2
		RenderHandOnScreen2(meshList[GEO_HAND], 5, 15.3, 1);
	}


	//PICKAXE
	if (equipPickaxe == true)
	{
		RenderPickaxeOnScreen(meshList[GEO_HOLDPICKAXE], 4.8, 14, 0.5);
	}

	//GUN
	if (equipGun == true)
	{
		RenderGunOnScreen(meshList[GEO_HOLDGUN], 3.4, 19.5, 4);
	}

	//// Player POS
	//std::ostringstream playerpos;
	//playerpos.str("");
	//playerpos << "Position: X(" << somePlayer.pos.x << ") Y(" << somePlayer.pos.y << ") Z(" << somePlayer.pos.z << ")";
	//RenderTextOnScreen(meshList[GEO_TEXT], playerpos.str(), Color(0, 1, 0), 1.2f, 3, 4);

	//// Collision check with asteroid  
	//std::ostringstream os;
	//os.str("");
	//os << "Collision with asteroids :" << AsteroidCollision;
	//RenderTextOnScreen(meshList[GEO_TEXT], os.str(), Color(0, 1, 0), 1.2f, 5, 5);


	//INSTRUCTIONS
	RenderInstructions();

	//NPC DIALOGUES
	RenderNPCDialogues();



	//Keypad
	for (vector<Keypad>::iterator i = keypads.begin(); i < keypads.end(); i++)
	{
		modelStack.PushMatrix();
		{
			modelStack.Translate(i->pos.x, i->pos.y + 15, i->pos.z);
			modelStack.Rotate(i->orientation, 0, 1, 0);
			modelStack.Scale(4.2f, 4.2f, 4.2f);
			RenderMesh(meshList[GEO_KEYPAD], true, toggleLight);
		}
		modelStack.PopMatrix();
	}

	//Note from Gary Goh: It's best to render the sprites first then the text.

	if (TokenOnScreen == true)
	{
		RenderTokenOnScreen(meshList[GEO_TOKEN], 5, 8, 6);
	}


	//PICK UP COKE
	if (RenderCoke == true)
	{
		RenderCokeOnScreen(meshList[GEO_COKE], 5, 8, 6);
	}



	//CROSS HAIR
	RenderTextOnScreen(meshList[GEO_TEXT], "+", Color(0, 1, 0), 2, 20, 17);

	//NPC DIALOGUES
	RenderNPCDialogues();



	//TEST TEXT
	//if (testText == true)
	//{
	//	RenderTextOnScreen(meshList[GEO_TEXT], "Press Y to look at the menu.", Color(0, 1, 0), 1.5, 5, 18);
	//	RenderTextOnScreen(meshList[GEO_TEXT], "Press U to eat the food.", Color(0, 1, 0), 1.5, 5, 16);
	//}

	// Ship Stats
	std::ostringstream shipStats;
	shipStats.str("");
	if (ShipList.size() > 0)
	{
		shipStats << "Speed(" << (int)ShipList[0].shipSpeed << ") Max(" << (int)ShipList[0].shipMaxSpeed << ") Landing(" << (int)ShipList[0].shipLandingSpeed << ")";
		RenderTextOnScreen(meshList[GEO_TEXT], shipStats.str(), Color(0, 1, 0), 2, 3, 10);
	}

	//// Tests for shipBuilding
	//if (askedHull)
	//{
	//    RenderTextOnScreen(meshList[GEO_TEXT], "Pick a Hull: 1. Light (10) | 2. Medium (20) | 3. Large (30) ", Color(1, 0, 0), 2, 0, 14);
	//}
	//if (askedWings)
	//{
	//    RenderTextOnScreen(meshList[GEO_TEXT], "Pick a Wing: 4. Dual (20) | 5. Quad (30)", Color(1, 0, 0), 2, 0, 14);
	//}
	//if (askedEngine)
	//{
	//    RenderTextOnScreen(meshList[GEO_TEXT], "Pick a Engine: 6. G1 Engine (20)  | 7. G2 Engine (30) ", Color(1, 0, 0), 2, 0, 14);
	//}

	// Tests for ship Flight
	if (thirdPersonCamera.yawingLeft) { RenderTextOnScreen(meshList[GEO_TEXT], "Left", Color(1, 0, 0), 1, 0, 14); }
	if (thirdPersonCamera.yawingRight) { RenderTextOnScreen(meshList[GEO_TEXT], "Right", Color(1, 0, 0), 1, 0, 15); }
	if (thirdPersonCamera.pitchingUp) { RenderTextOnScreen(meshList[GEO_TEXT], "Up", Color(1, 0, 0), 1, 0, 13); }
	if (thirdPersonCamera.pitchingDown) { RenderTextOnScreen(meshList[GEO_TEXT], "Down", Color(1, 0, 0), 1, 0, 12); }

	if (deadText) { RenderHealthBarOnScreen(meshList[GEO_DEADHEALTHBAR], 2.6, 2.5, 21); }
	else { RenderHealthBarOnScreen(meshList[GEO_ALIVEHEALTHBAR], 2.6, 2.5, 21); }
}

//Initialise maze mesh, position and collision.
void SP2::initMaze()
{
	meshList[GEO_MAZE_SIDE_WALL] = MeshBuilder::GenerateOBJ("mazeSideWall", "OBJ//Maze//mazeSideWalls.obj");
	meshList[GEO_MAZE_SIDE_WALL]->textureID = LoadTGA("Image//Maze//mazewallUV.tga");

	meshList[GEO_MAZE_OBSTACLE] = MeshBuilder::GenerateOBJ("mazeObstacle", "OBJ//Maze//mazeObstacle.obj");
	meshList[GEO_MAZE_OBSTACLE]->textureID = LoadTGA("Image//Maze//mazewallUV.tga");

	meshList[GEO_MAZE_ROOF] = MeshBuilder::GenerateOBJ("mazeRoof", "OBJ//Maze//mazeRoof.obj");
	meshList[GEO_MAZE_ROOF]->textureID = LoadTGA("Image//Maze//mazewallUV.tga");

	meshList[GEO_MAZE_TREASURE] = MeshBuilder::GenerateOBJ("mazeTreasure", "OBJ//Maze//mazeTreasure.obj");
	meshList[GEO_MAZE_TREASURE]->textureID = LoadTGA("Image//Maze//mazeTreasureUV.tga");

	meshList[GEO_PEDASTAL] = MeshBuilder::GenerateOBJ("pedastal", "OBJ//Maze//pedastal.obj");
	meshList[GEO_PEDASTAL]->textureID = LoadTGA("Image//Maze//pedestalUV.tga");

	meshList[GEO_LAVA] = MeshBuilder::GenerateOBJ("lava", "OBJ//lava.obj");
	meshList[GEO_LAVA]->textureID = LoadTGA("Image//lavaUV.tga");

	meshList[GEO_SIGNBOARD] = MeshBuilder::GenerateOBJ("signboard", "OBJ//HelipadSignBoard.obj");
	meshList[GEO_SIGNBOARD]->textureID = LoadTGA("Image//Maze//MazeSignBoard.tga");

	int i = 0;
	for (int zAxis = 300; zAxis >= -400; zAxis -= 100)
	{
		InteractableOBJs leftWall = InteractableOBJs("leftWall", meshList[GEO_MAZE_SIDE_WALL]->maxPos, meshList[GEO_MAZE_SIDE_WALL]->minPos, Position(-420, 10, zAxis), 30, 0, Vector3(0, 0, 0));
		InteractablesList.push_back(leftWall);

		InteractableOBJs rightWall = InteractableOBJs("rightWall", meshList[GEO_MAZE_SIDE_WALL]->maxPos, meshList[GEO_MAZE_SIDE_WALL]->minPos, Position(-280, 10, zAxis), 30, 0, Vector3(0, 0, 0));
		InteractablesList.push_back(rightWall);

		InteractableOBJs leftObstacle = InteractableOBJs("leftObstacle", meshList[GEO_MAZE_OBSTACLE]->maxPos, meshList[GEO_MAZE_OBSTACLE]->minPos, Position(-420 + mazeRandomTranslateVec[i], 10, zAxis + mazeRandomTranslateVec[i]), 30, 0, Vector3(0, 0, 0));
		InteractablesList.push_back(leftObstacle);

		InteractableOBJs rightObstacle = InteractableOBJs("rightObstacle", meshList[GEO_MAZE_OBSTACLE]->maxPos, meshList[GEO_MAZE_OBSTACLE]->minPos, Position(-280 + mazeRandomTranslateVec[i], 10, zAxis + mazeRandomTranslateVec[i]), 30, 0, Vector3(0, 0, 0));
		InteractablesList.push_back(rightObstacle);

		InteractableOBJs mazeRoof = InteractableOBJs("mazeRoof", meshList[GEO_MAZE_ROOF]->maxPos, meshList[GEO_MAZE_ROOF]->minPos, Position(-350, 32, zAxis), 30, 0, Vector3(0, 0, 0));
		InteractablesList.push_back(mazeRoof);

		InteractableOBJs lava = InteractableOBJs("lava", meshList[GEO_LAVA]->maxPos, meshList[GEO_LAVA]->minPos, Position(-420, 10, zAxis), 30, 0, Vector3(0, 0, 0));
		InteractablesList.push_back(lava);

		++i;
	}

    InteractableOBJs mazeTreasure = InteractableOBJs("mazeTreasure", meshList[GEO_MAZE_TREASURE]->maxPos, meshList[GEO_MAZE_TREASURE]->minPos, Position(-350, 15, -370), 5, 0, Vector3(0, 0, 0));
    mazeTreasure.setRequirements(25, 12);
    InteractablesList.push_back(mazeTreasure);

	InteractableOBJs pedastal = InteractableOBJs("pedastal", meshList[GEO_PEDASTAL]->maxPos, meshList[GEO_PEDASTAL]->minPos, Position(-350, 0, -370), 10, 0, Vector3(0, 0, 0));
	InteractablesList.push_back(pedastal);

	InteractableOBJs signboard = InteractableOBJs("signboard", meshList[GEO_SIGNBOARD]->maxPos, meshList[GEO_SIGNBOARD]->minPos, Position(-370, 0, 370), 5, 0, Vector3(0, 0, 0));
	InteractablesList.push_back(signboard);

}

//Initialise safe
void SP2::InitSafe()
{
	InteractableOBJs keypadOBJ =
	{
		"keypad",
		meshList[GEO_KEYPAD]->maxPos,
		meshList[GEO_KEYPAD]->minPos,
		{},
		1,
		0,
		{}
	};

	InteractableOBJs safeOBJ =
	{
		"safe",
		meshList[GEO_SAFE_BOX]->maxPos,
		meshList[GEO_SAFE_BOX]->minPos,
		{ 86.5f, 16, -143.f },
		1,
		0,
		{}
	};

	safeOBJ.maxPos.x = 20;
	safeOBJ.minPos.x = -20;
	safeOBJ.minPos.y = -20;
	safeOBJ.maxPos.z = 12;
	safeOBJ.setRequirements(1, 0.1f);
	InteractablesList.push_back(safeOBJ);

	keypad =
	{
		safeOBJ.pos,
		0
	};
	keypad.targetBool.setTargetLocation(&isSafeOpen);

	keypadOBJ.setRequirements(14, 0.45f);
	keypadOBJ.minPos = { 0.5f, 0.5f, 0.5f };
	keypadOBJ.maxPos = { 0.5f, 0.5f, 0.5f };
	keypadOBJ.pos = keypad.pos;
	keypadOBJ.pos.z += 1;


	const float d = 1.25f;

	keypadOBJ.name = "keypadButton1";
	keypadOBJ.pos.x += d * -1;
	keypadOBJ.pos.y += d * 1;
	InteractablesList.push_back(keypadOBJ);

	keypadOBJ.name = "keypadButton2";
	keypadOBJ.pos.x += d * 1;
	keypadOBJ.pos.y += d * 0;
	InteractablesList.push_back(keypadOBJ);

	keypadOBJ.name = "keypadButton3";
	keypadOBJ.pos.x += d * 1;
	keypadOBJ.pos.y += d * 0;
	InteractablesList.push_back(keypadOBJ);

	keypadOBJ.name = "keypadButton4";
	keypadOBJ.pos.x += d * -2;
	keypadOBJ.pos.y += d * -1;
	InteractablesList.push_back(keypadOBJ);

	keypadOBJ.name = "keypadButton5";
	keypadOBJ.pos.x += d * 1;
	keypadOBJ.pos.y += d * 0;
	InteractablesList.push_back(keypadOBJ);

	keypadOBJ.name = "keypadButton6";
	keypadOBJ.pos.x += d * 1;
	keypadOBJ.pos.y += d * 0;
	InteractablesList.push_back(keypadOBJ);

	keypadOBJ.name = "keypadButton7";
	keypadOBJ.pos.x += d * -2;
	keypadOBJ.pos.y += d * -1;
	InteractablesList.push_back(keypadOBJ);

	keypadOBJ.name = "keypadButton8";
	keypadOBJ.pos.x += d * 1;
	keypadOBJ.pos.y += d * 0;
	InteractablesList.push_back(keypadOBJ);

	keypadOBJ.name = "keypadButton9";
	keypadOBJ.pos.x += d * 1;
	keypadOBJ.pos.y += d * 0;
	InteractablesList.push_back(keypadOBJ);

	keypadOBJ.name = "keypadButton0";
	keypadOBJ.pos.x += d * -1;
	keypadOBJ.pos.y += d * -1;
	InteractablesList.push_back(keypadOBJ);
}

//Initialise mountains mesh, position and collision.
void SP2::initMountains()
{
	meshList[GEO_MOUNTAIN] = MeshBuilder::GenerateOBJ("moutain", "OBJ//Mountain.obj");
	meshList[GEO_MOUNTAIN]->textureID = LoadTGA("Image//spaceground.tga");

	for (int zAxis = 500; zAxis >= -500; zAxis -= 100)
	{
		InteractableOBJs mountain1 = InteractableOBJs("mountain", meshList[GEO_MOUNTAIN]->maxPos, meshList[GEO_MOUNTAIN]->minPos, Position(-160, 0, zAxis), 5, 0, Vector3(0, 0, 0));
		InteractablesList.push_back(mountain1);

		InteractableOBJs mountain2 = InteractableOBJs("mountain", meshList[GEO_MOUNTAIN]->maxPos, meshList[GEO_MOUNTAIN]->minPos, Position(550, 0, zAxis), 5, 0, Vector3(0, 0, 0));
		InteractablesList.push_back(mountain2);

		InteractableOBJs mountain3 = InteractableOBJs("mountain", meshList[GEO_MOUNTAIN]->maxPos, meshList[GEO_MOUNTAIN]->minPos, Position(-550, 0, zAxis), 5, 0, Vector3(0, 0, 0));
		InteractablesList.push_back(mountain3);
	}

	for (int xAxis = 500; xAxis >= -500; xAxis -= 100)
	{
		InteractableOBJs mountain4 = InteractableOBJs("mountain", meshList[GEO_MOUNTAIN]->maxPos, meshList[GEO_MOUNTAIN]->minPos, Position(xAxis, 0, 600), 5, 0, Vector3(0, 0, 0));
		InteractablesList.push_back(mountain4);

		InteractableOBJs mountain5 = InteractableOBJs("mountain", meshList[GEO_MOUNTAIN]->maxPos, meshList[GEO_MOUNTAIN]->minPos, Position(xAxis, 0, -500), 5, 0, Vector3(0, 0, 0));
		InteractablesList.push_back(mountain5);
	}
}

void SP2::renderMaze()
{
	Vector3 mazeScale(30, 35, 30);
	int i = 0;

	// Left & Right Side Walls
	for (int zAxis = 300; zAxis >= -400; zAxis -= 100)
	{
		// Left Wall
		modelStack.PushMatrix();
		modelStack.Translate(-420, 10, zAxis);
		modelStack.Scale(mazeScale.x, mazeScale.y, mazeScale.z);
		RenderMesh(meshList[GEO_MAZE_SIDE_WALL], true, toggleLight);
		modelStack.PopMatrix();

		// Right Wall
		modelStack.PushMatrix();
		modelStack.Translate(-280, 10, zAxis);
		modelStack.Scale(mazeScale.x, mazeScale.y, mazeScale.z);
		RenderMesh(meshList[GEO_MAZE_SIDE_WALL], true, toggleLight);
		modelStack.PopMatrix();

		// Roof
		modelStack.PushMatrix();
		modelStack.Translate(-350, 31, zAxis);
		modelStack.Scale(mazeScale.x, mazeScale.y, mazeScale.z - 15);
		RenderMesh(meshList[GEO_MAZE_ROOF], true, toggleLight);
		modelStack.PopMatrix();


		// Obstacles
		// Left Side Obstacles
		modelStack.PushMatrix();
		modelStack.Translate(-420 + mazeTranslateValue + mazeRandomTranslateVec[i], 10, zAxis + mazeRandomTranslateVec[i]);
		modelStack.Scale(mazeScale.x, mazeScale.y, mazeScale.z);
		RenderMesh(meshList[GEO_MAZE_OBSTACLE], true, toggleLight);
		modelStack.PopMatrix();

		// Right Side Obstacles
		modelStack.PushMatrix();
		modelStack.Translate(-280 + mazeTranslateValue + mazeRandomTranslateVec[i], 10, zAxis + mazeRandomTranslateVec[i]);
		modelStack.Scale(mazeScale.x, mazeScale.y, mazeScale.z);
		RenderMesh(meshList[GEO_MAZE_OBSTACLE], true, toggleLight);
		modelStack.PopMatrix();

		// Lava (1st)
		modelStack.PushMatrix();
		modelStack.Translate(-420 + lavaTranslation, 0, zAxis);
		modelStack.Scale(mazeScale.x, mazeScale.y, mazeScale.z + 5);
		RenderMesh(meshList[GEO_LAVA], true, toggleLight);
		modelStack.PopMatrix();

		// Lava (2nd)
		modelStack.PushMatrix();
		modelStack.Translate(-280 - lavaTranslation, 0, zAxis);
		modelStack.Scale(mazeScale.x, mazeScale.y, mazeScale.z + 5);
		RenderMesh(meshList[GEO_LAVA], true, toggleLight);
		modelStack.PopMatrix();

		++i;
	}

    // Treasure + Pedastal
    modelStack.PushMatrix();
    modelStack.Translate(-350, 0, -370);
    modelStack.Scale(5, 10, 5);
    RenderMesh(meshList[GEO_PEDASTAL], true, toggleLight);
    modelStack.PopMatrix();

    if (!treasureTaken)
    {
        modelStack.PushMatrix();
        modelStack.Translate(-350, 15, -370);
        modelStack.Scale(2, 2, 2);
        RenderMesh(meshList[GEO_MAZE_TREASURE], true, toggleLight);
        modelStack.PopMatrix();
    }


    // SignBoard
    modelStack.PushMatrix();
    modelStack.Translate(-370, 0, 370);
    modelStack.Scale(5, 5, 5);
    RenderMesh(meshList[GEO_SIGNBOARD], true, toggleLight);
    modelStack.PopMatrix();
}

//Room template
void SP2::initRoomTemplate(Position pos, Vector3 size, int groundMeshSize)
{
	Building floor1 = Building("floor1", meshList[GEO_GROUND]->maxPos, meshList[GEO_GROUND]->minPos, Position(pos.x, pos.y, pos.z - 20), groundMeshSize, 0, Vector3(0, 0, 0));
	BuildingsList.push_back(floor1);

	Building ceiling1 = Building("ceiling1", meshList[GEO_GROUND]->maxPos, meshList[GEO_GROUND]->minPos, Position(pos.x, pos.y + 30, pos.z - 20), groundMeshSize, 0, Vector3(0, 0, 0));
	BuildingsList.push_back(ceiling1);


	Building rightWall1 = Building("rightWall1", meshList[GEO_WALL]->maxPos, meshList[GEO_WALL]->minPos, Position(pos.x + 38, pos.y + heightOfWall, pos.z + (groundMeshSize / 2)), 13, 0, Vector3(0, 0, 0));
	BuildingsList.push_back(rightWall1);

	Building rightWall2 = Building("rightWall2", meshList[GEO_WALL]->maxPos, meshList[GEO_WALL]->minPos, Position(pos.x - 38, pos.y + heightOfWall, pos.z + (groundMeshSize / 2)), 13, 0, Vector3(0, 0, 0));
	BuildingsList.push_back(rightWall2);

	Building rightWall1top = Building("rightTop1", meshList[GEO_WALL]->maxPos, meshList[GEO_WALL]->minPos, Position(pos.x + 38, pos.y + 2 * heightOfWall, pos.z + (groundMeshSize / 2)), 13, 0, Vector3(0, 0, 0));
	BuildingsList.push_back(rightWall1top);

	Building rightWall2top = Building("rightTop2", meshList[GEO_WALL]->maxPos, meshList[GEO_WALL]->minPos, Position(pos.x - 38, pos.y + 2 * heightOfWall, pos.z + (groundMeshSize / 2)), 13, 0, Vector3(0, 0, 0));
	BuildingsList.push_back(rightWall2top);

	InteractableOBJs rightGateTop = InteractableOBJs("rightGateTop", meshList[GEO_GATETOP]->maxPos, meshList[GEO_GATETOP]->minPos, Position(pos.x, pos.y + 15, pos.z + (groundMeshSize / 2)), 5, 0, Vector3(0, 0, 0));
	rightGateTop.setRequirements(30, 200);
	InteractablesList.push_back(rightGateTop);


	Building leftWall1 = Building("leftWall1", meshList[GEO_WALL]->maxPos, meshList[GEO_WALL]->minPos, Position(pos.x + 38, pos.y + heightOfWall, pos.z - (groundMeshSize / 2)), 13, 0, Vector3(0, 0, 0));
	BuildingsList.push_back(leftWall1);

	Building leftWall2 = Building("leftWall2", meshList[GEO_WALL]->maxPos, meshList[GEO_WALL]->minPos, Position(pos.x - 38, pos.y + heightOfWall, pos.z - (groundMeshSize / 2)), 13, 0, Vector3(0, 0, 0));
	BuildingsList.push_back(leftWall2);

	Building leftWall1top = Building("leftTop1", meshList[GEO_WALL]->maxPos, meshList[GEO_WALL]->minPos, Position(pos.x + 38, pos.y + 2 * heightOfWall, pos.z - (groundMeshSize / 2)), 13, 0, Vector3(0, 0, 0));
	BuildingsList.push_back(leftWall1top);

	Building leftWall2top = Building("leftTop2", meshList[GEO_WALL]->maxPos, meshList[GEO_WALL]->minPos, Position(pos.x - 38, pos.y + 2 * heightOfWall, pos.z - (groundMeshSize / 2)), 13, 0, Vector3(0, 0, 0));
	BuildingsList.push_back(leftWall2top);

	InteractableOBJs leftGateTop = InteractableOBJs("leftGateTop", meshList[GEO_GATETOP]->maxPos, meshList[GEO_GATETOP]->minPos, Position(pos.x, pos.y + 15, pos.z - (groundMeshSize / 2)), 5, 0, Vector3(0, 0, 0));
	leftGateTop.setRequirements(30, 200);
	InteractablesList.push_back(leftGateTop);


	Building frontWall1 = Building("frontWall1", meshList[GEO_WALL2]->maxPos, meshList[GEO_WALL2]->minPos, Position(pos.x + (groundMeshSize / 2), pos.y + heightOfWall, pos.z - 38), 13, 0, Vector3(0, 0, 0));
	BuildingsList.push_back(frontWall1);

	Building frontWall2 = Building("frontWall2", meshList[GEO_WALL2]->maxPos, meshList[GEO_WALL2]->minPos, Position(pos.x + (groundMeshSize / 2), pos.y + heightOfWall, pos.z + 38), 13, 0, Vector3(0, 0, 0));
	BuildingsList.push_back(frontWall2);

	Building frontWall1top = Building("frontTop1", meshList[GEO_WALL2]->maxPos, meshList[GEO_WALL2]->minPos, Position(pos.x + (groundMeshSize / 2), pos.y + 2 * heightOfWall, pos.z - 38), 13, 0, Vector3(0, 0, 0));
	BuildingsList.push_back(frontWall1top);

	Building frontWall2top = Building("frontTop2", meshList[GEO_WALL2]->maxPos, meshList[GEO_WALL2]->minPos, Position(pos.x + (groundMeshSize / 2), pos.y + 2 * heightOfWall, pos.z + 38), 13, 0, Vector3(0, 0, 0));
	BuildingsList.push_back(frontWall2top);

	InteractableOBJs frontGateTop = InteractableOBJs("frontGateTop", meshList[GEO_GATETOP2]->maxPos, meshList[GEO_GATETOP2]->minPos, Position(pos.x + (groundMeshSize / 2), pos.y + 15, pos.z), 5, 0, Vector3(0, 0, 0));
	frontGateTop.setRequirements(30, 200);
	InteractablesList.push_back(frontGateTop);


	Building backWall1 = Building("backWall1", meshList[GEO_WALL2]->maxPos, meshList[GEO_WALL2]->minPos, Position(pos.x - (groundMeshSize / 2), pos.y + heightOfWall, pos.z - 38), 13, 0, Vector3(0, 0, 0));
	BuildingsList.push_back(backWall1);

	Building backWall2 = Building("backWall2", meshList[GEO_WALL2]->maxPos, meshList[GEO_WALL2]->minPos, Position(pos.x - (groundMeshSize / 2), pos.y + heightOfWall, pos.z + 38), 13, 0, Vector3(0, 0, 0));
	BuildingsList.push_back(backWall2);

	Building backWall1top = Building("backTop1", meshList[GEO_WALL2]->maxPos, meshList[GEO_WALL2]->minPos, Position(pos.x - (groundMeshSize / 2), pos.y + 2 * heightOfWall, pos.z - 38), 13, 0, Vector3(0, 0, 0));
	BuildingsList.push_back(backWall1top);

	Building backWall2top = Building("backTop2", meshList[GEO_WALL2]->maxPos, meshList[GEO_WALL2]->minPos, Position(pos.x - (groundMeshSize / 2), pos.y + 2 * heightOfWall, pos.z + 38), 13, 0, Vector3(0, 0, 0));
	BuildingsList.push_back(backWall2top);

	InteractableOBJs backGateTop = InteractableOBJs("backGateTop", meshList[GEO_GATETOP2]->maxPos, meshList[GEO_GATETOP2]->minPos, Position(pos.x - (groundMeshSize / 2), pos.y + 15, pos.z), 5, 0, Vector3(0, 0, 0));
	backGateTop.setRequirements(30, 200);
	InteractablesList.push_back(backGateTop);

}

void SP2::ReadKeyPresses()
{
	if (Application::IsKeyPressed('1'))
	{
		glEnable(GL_CULL_FACE);
	}
	if (Application::IsKeyPressed('2'))
	{
		glDisable(GL_CULL_FACE);
	}

	if (Application::IsKeyPressed('B'))
	{
		if (toggleLight == true)
		{
			toggleLight = false;
		}
		else
		{
			toggleLight = true;
		}
	}

	if (Application::IsKeyPressed('C'))
	{
		isInViewSpheres = true;
	}

	if (Application::IsKeyPressed('V'))
	{
		isInViewSpheres = false;
	}
}

void SP2::RenderInstructions()
{
	//VENDING TEXT
	if (NearVendingText)
	{
		RenderNPCTextBoxOnScreen(meshList[GEO_INSTRUCTIONBOX], 5, 8, 2.8);
		RenderTextOnScreen(meshList[GEO_TEXT], instruct_vec[0], Color(1, 0, 0), 1.7, 5, 10);
		RenderTextOnScreen(meshList[GEO_TEXT], instruct_vec[9], Color(1, 0, 0), 1.7, 5, 8);
	}

	//CRYSTAL TEXT
	if (CrystalText == true)
	{
		RenderNPCTextBoxOnScreen(meshList[GEO_INSTRUCTIONBOX], 5, 8, 2.8);
		RenderTextOnScreen(meshList[GEO_TEXT], instruct_vec[1], Color(1, 0, 0), 1.7, 5, 10);
		RenderTextOnScreen(meshList[GEO_TEXT], instruct_vec[2], Color(1, 0, 0), 1.7, 5, 8);
	}

	//PICK UP TOKEN
	if (PickUpTokenText == true)
	{
		RenderNPCTextBoxOnScreen(meshList[GEO_INSTRUCTIONBOX], 5, 8, 2.8);
		RenderTextOnScreen(meshList[GEO_TEXT], instruct_vec[3], Color(1, 0, 0), 1.7, 5, 10);
		RenderTextOnScreen(meshList[GEO_TEXT], instruct_vec[4], Color(1, 0, 0), 1.7, 5, 8);
	}

	//CONSUME COKE TEXT
	if (ConsumeCokeText == true)
	{
		RenderNPCTextBoxOnScreen(meshList[GEO_INSTRUCTIONBOX], 5, 8, 2.8);
		RenderTextOnScreen(meshList[GEO_TEXT], instruct_vec[5], Color(1, 0, 0), 1.7, 5, 10);
		RenderTextOnScreen(meshList[GEO_TEXT], instruct_vec[6], Color(1, 0, 0), 1.7, 5, 8);
	}

	//WEAR SUIT TEXT
	if (wearSuitText == true)
	{
		RenderNPCTextBoxOnScreen(meshList[GEO_INSTRUCTIONBOX], 5, 8, 2.8);
		RenderTextOnScreen(meshList[GEO_TEXT], instruct_vec[7], Color(1, 0, 0), 1.7, 5, 10);
	}

	//WEAR SUIT \ MASK ON SCREEN
	if (wearSuit == true)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], instruct_vec[8], Color(1, 0, 0), 2, 8, 14);

		glBlendFunc(1, 1);
		RenderSpacemaskOnScreen(meshList[GEO_SPACEMASK], 5, 8, 6.3);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

    if (treasureText)
    {
        RenderNPCTextBoxOnScreen(meshList[GEO_INSTRUCTIONBOX], 5, 8, 2.8);
        RenderTextOnScreen(meshList[GEO_TEXT], instruct_vec[10], Color(1, 0, 0), 1.7, 5, 10);
        RenderTextOnScreen(meshList[GEO_TEXT], instruct_vec[11], Color(1, 0, 0), 1.7, 5, 8);
    }
}

void SP2::RenderNPCDialogues()
{
	if (chefText == true)  //true
	{
		RenderNPCTextBoxOnScreen(meshList[GEO_NPCDIALOGUEBOX], 5, 8, 2.8);
		RenderTextOnScreen(meshList[GEO_TEXT], dialogue_vec[0], Color(1, 0, 0), 1.7, 5, 10);
		RenderTextOnScreen(meshList[GEO_TEXT], "Press Y to look at the menu.", Color(1, 1, 1), 1.7, 5, 8);
		RenderTextOnScreen(meshList[GEO_TEXT], "Press U to eat the food.", Color(1, 1, 1), 1.7, 5, 6);
	}

	if (spaceguyText == true)
	{
		RenderNPCTextBoxOnScreen(meshList[GEO_NPCDIALOGUEBOX], 5, 8, 2.8);
		RenderTextOnScreen(meshList[GEO_TEXT], dialogue_vec[1], Color(1, 0, 0), 1.7, 5, 10);
	}

	if (nurseText == true)
	{
		RenderNPCTextBoxOnScreen(meshList[GEO_NPCDIALOGUEBOX], 5, 8, 2.8);
		RenderTextOnScreen(meshList[GEO_TEXT], dialogue_vec[2], Color(1, 0, 0), 1.7, 5, 10);
	}

	if (doctorText == true)
	{
		RenderNPCTextBoxOnScreen(meshList[GEO_NPCDIALOGUEBOX], 5, 8, 2.8);
		RenderTextOnScreen(meshList[GEO_TEXT], dialogue_vec[3], Color(1, 0, 0), 1.7, 5, 10);
	}

	if (traderText == true)   //true
	{
		RenderNPCTextBoxOnScreen(meshList[GEO_NPCDIALOGUEBOX], 5, 8, 2.8);
		RenderTextOnScreen(meshList[GEO_TEXT], dialogue_vec[4], Color(1, 0, 0), 1.7, 5, 10);
		RenderTextOnScreen(meshList[GEO_TEXT], dialogue_vec[6], Color(1, 1, 1), 1.7, 5, 8);
	}

	if (soldierText == true)
	{
		RenderNPCTextBoxOnScreen(meshList[GEO_NPCDIALOGUEBOX], 5, 8, 2.8);
		RenderTextOnScreen(meshList[GEO_TEXT], dialogue_vec[5], Color(1, 0, 0), 1.7, 5, 10);
		RenderTextOnScreen(meshList[GEO_TEXT], dialogue_vec[7], Color(1, 1, 1), 1.7, 5, 8);
	}

	if (NPCInCafeTokenTask == true)
	{
		RenderNPCTextBoxOnScreen(meshList[GEO_NPCDIALOGUEBOX], 5, 8, 2.8);
		RenderTextOnScreen(meshList[GEO_TEXT], dialogue_vec[8], Color(1, 0, 0), 1.7, 5, 10);
		RenderTextOnScreen(meshList[GEO_TEXT], dialogue_vec[9], Color(1, 0, 0), 1.7, 5, 8);
	}

	if (NPCInRecMazeTask == true)
	{
		RenderNPCTextBoxOnScreen(meshList[GEO_NPCDIALOGUEBOX], 5, 8, 2.8);
		RenderTextOnScreen(meshList[GEO_TEXT], dialogue_vec[10], Color(1, 0, 0), 1.7, 5, 10);
		RenderTextOnScreen(meshList[GEO_TEXT], dialogue_vec[11], Color(1, 0, 0), 1.7, 5, 8);
		RenderTextOnScreen(meshList[GEO_TEXT], dialogue_vec[12], Color(1, 0, 0), 1.7, 5, 6);
	}

}

void SP2::RenderRoomTemplate(Position pos, Vector3 size, int groundMeshSize)
{
	groundMeshSize = 100;

	// Whole Room
	modelStack.PushMatrix();
	modelStack.Translate(pos.x, pos.y, pos.z);

	// Render Floor + Ceiling
	modelStack.PushMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(groundMeshSize, groundMeshSize, groundMeshSize);
	RenderMesh(meshList[GEO_GROUND], false, toggleLight); // Floor
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 30, 0);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Scale(groundMeshSize, groundMeshSize, groundMeshSize);
	RenderMesh(meshList[GEO_GROUND], false, toggleLight); // Ceiling
	modelStack.PopMatrix();

	modelStack.PopMatrix();

	// Render Walls
	modelStack.PushMatrix();

	// ---------------------------- Right Wall ---------------------------------- //
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, (groundMeshSize / 2));

	modelStack.PushMatrix();
	modelStack.Translate(38, heightOfWall, 0);
	modelStack.Scale(13, 30, 13);
	RenderMesh(meshList[GEO_WALL], false, toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-38, heightOfWall, 0);
	modelStack.Scale(13, 30, 13);
	RenderMesh(meshList[GEO_WALL], false, toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 15 + rightGateOffset, 0);
	modelStack.Scale(3, 9, 3);
	RenderMesh(meshList[GEO_GATETOP], false, toggleLight);
	modelStack.PopMatrix();

	modelStack.PopMatrix();
	// ---------------------------- Right Wall ---------------------------------- //


	// ---------------------------- Left Wall ---------------------------------- //
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -(groundMeshSize / 2));

	modelStack.PushMatrix();
	modelStack.Translate(38, heightOfWall, 0);
	modelStack.Scale(13, 30, 13);
	RenderMesh(meshList[GEO_WALL], false, toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-38, heightOfWall, 0);
	modelStack.Scale(13, 30, 13);
	RenderMesh(meshList[GEO_WALL], false, toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 15 + leftGateOffset, 0);
	modelStack.Scale(3, 9, 3);
	RenderMesh(meshList[GEO_GATETOP], false, toggleLight);
	modelStack.PopMatrix();

	modelStack.PopMatrix();
	// ---------------------------- Left Wall ---------------------------------- //


	// ---------------------------- Front Wall ---------------------------------- //
	modelStack.PushMatrix();
	modelStack.Translate((groundMeshSize / 2), 0, 0);

	modelStack.PushMatrix();
	modelStack.Translate(0, heightOfWall, -38);
	modelStack.Scale(13, 30, 13);
	RenderMesh(meshList[GEO_WALL2], false, toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, heightOfWall, 38);
	modelStack.Scale(13, 30, 13);
	RenderMesh(meshList[GEO_WALL2], false, toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 15 + frontGateOffset, 0);
	modelStack.Scale(3, 9, 3);
	RenderMesh(meshList[GEO_GATETOP2], false, toggleLight);
	modelStack.PopMatrix();

	modelStack.PopMatrix();
	// ---------------------------- Front Wall ---------------------------------- //


	// ---------------------------- Back Wall ---------------------------------- //
	modelStack.PushMatrix();
	modelStack.Translate((-groundMeshSize / 2), 0, 0);

	modelStack.PushMatrix();
	modelStack.Translate(0, heightOfWall, -38);
	modelStack.Scale(13, 30, 13);
	RenderMesh(meshList[GEO_WALL2], false, toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, heightOfWall, 38);
	modelStack.Scale(13, 30, 13);
	RenderMesh(meshList[GEO_WALL2], false, toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 15 + backGateOffset, 0);
	modelStack.Scale(3, 9, 3);
	RenderMesh(meshList[GEO_GATETOP2], false, toggleLight);
	modelStack.PopMatrix();

	modelStack.PopMatrix();
	// ---------------------------- Back Wall ---------------------------------- //

	modelStack.PopMatrix();

	modelStack.PopMatrix();

}

void SP2::RenderSkybox()
{
	// FRONT
	modelStack.PushMatrix();

	modelStack.Translate(somePlayer.pos.x, somePlayer.pos.y, -500 + somePlayer.pos.z);

	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_FRONT], false, toggleLight);
	modelStack.PopMatrix();

	// BACK
	modelStack.PushMatrix();

	//if (somePlayer.getCameraType() == "first")
	//{
	//	modelStack.Translate(firstPersonCamera.position.x, firstPersonCamera.position.y, 249.5 + firstPersonCamera.position.z);
	//}
	//else
	//{
	//	modelStack.Translate(thirdPersonCamera.position.x, thirdPersonCamera.position.y, 249.5 + thirdPersonCamera.position.z);
	//}

	modelStack.Translate(somePlayer.pos.x, somePlayer.pos.y, 500 + somePlayer.pos.z);

	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_BACK], false, toggleLight);
	modelStack.PopMatrix();

	// LEFT
	modelStack.PushMatrix();

	//if (somePlayer.getCameraType() == "first")
	//{
	//	modelStack.Translate(-249.5 + firstPersonCamera.position.x, firstPersonCamera.position.y, firstPersonCamera.position.z);
	//}
	//else
	//{
	//	modelStack.Translate(-249.5 + thirdPersonCamera.position.x, thirdPersonCamera.position.y, thirdPersonCamera.position.z);
	//}

	modelStack.Translate(-500 + somePlayer.pos.x, somePlayer.pos.y, somePlayer.pos.z);

	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Rotate(0, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_LEFT], false, toggleLight);
	modelStack.PopMatrix();

	// RIGHT
	modelStack.PushMatrix();

	//if (somePlayer.getCameraType() == "first")
	//{
	//	modelStack.Translate(249.5 + firstPersonCamera.position.x, firstPersonCamera.position.y, firstPersonCamera.position.z);
	//}
	//else
	//{
	//	modelStack.Translate(249.5 + thirdPersonCamera.position.x, thirdPersonCamera.position.y, thirdPersonCamera.position.z);
	//}

	modelStack.Translate(500 + somePlayer.pos.x, somePlayer.pos.y, somePlayer.pos.z);

	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_RIGHT], false, toggleLight);
	modelStack.PopMatrix();

	// BOTTOM
	modelStack.PushMatrix();

	//if (somePlayer.getCameraType() == "first")
	//{
	//	modelStack.Translate(firstPersonCamera.position.x, -249.5 + firstPersonCamera.position.y, firstPersonCamera.position.z);
	//}
	//else
	//{
	//	modelStack.Translate(thirdPersonCamera.position.x, -249.5 + thirdPersonCamera.position.y, thirdPersonCamera.position.z);
	//}
	//modelStack.Scale(500, 500, 500);

	modelStack.Translate(somePlayer.pos.x, -500 + somePlayer.pos.y, somePlayer.pos.z);
	modelStack.Scale(1000, 1000, 1000);

	RenderMesh(meshList[GEO_BOTTOM], false, toggleLight);
	modelStack.PopMatrix();

	// TOP
	modelStack.PushMatrix();

	//if (somePlayer.getCameraType() == "first")
	//{
	//	modelStack.Translate(firstPersonCamera.position.x, 249.5 + firstPersonCamera.position.y, firstPersonCamera.position.z);
	//}
	//else
	//{
	//	modelStack.Translate(thirdPersonCamera.position.x, 249.5 + thirdPersonCamera.position.y, thirdPersonCamera.position.z);
	//}

	modelStack.Translate(somePlayer.pos.x, 500 + somePlayer.pos.y, somePlayer.pos.z);

	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_TOP], false, toggleLight);
	modelStack.PopMatrix();
}

void SP2::RenderBunkRoom()
{
	//BUNK 1 
	modelStack.PushMatrix();
	modelStack.Translate(288, 3, 127);
	modelStack.Scale(1.2, 1.2, 1.2);
	RenderMesh(meshList[GEO_BUNK], true, toggleLight);
	modelStack.PopMatrix();

	//BUNK 2 
	modelStack.PushMatrix();
	modelStack.Translate(271, 3, 127);
	modelStack.Scale(1.2, 1.2, 1.2);
	RenderMesh(meshList[GEO_BUNK], true, toggleLight);
	modelStack.PopMatrix();


	//BUNK 3 
	modelStack.PushMatrix();
	modelStack.Translate(210, 3, 127);
	modelStack.Scale(1.2, 1.2, 1.2);
	RenderMesh(meshList[GEO_BUNK], true, toggleLight);
	modelStack.PopMatrix();

	//BUNK 4 
	modelStack.PushMatrix();
	modelStack.Translate(227, 3, 127);
	modelStack.Scale(1.2, 1.2, 1.2);
	RenderMesh(meshList[GEO_BUNK], true, toggleLight);
	modelStack.PopMatrix();



	//BUNK 5 
	modelStack.PushMatrix();
	modelStack.Translate(288, 3, 191.5);
	modelStack.Scale(1.2, 1.2, 1.2);
	modelStack.Rotate(180, 0, 1, 0);
	RenderMesh(meshList[GEO_BUNK], true, toggleLight);
	modelStack.PopMatrix();

	//BUNK 6 
	modelStack.PushMatrix();
	modelStack.Translate(271, 3, 191.5);
	modelStack.Scale(1.2, 1.2, 1.2);
	modelStack.Rotate(180, 0, 1, 0);
	RenderMesh(meshList[GEO_BUNK], true, toggleLight);
	modelStack.PopMatrix();

	//SPACE MAN RANDOM NPC
	modelStack.PushMatrix();
	modelStack.Translate(271, 1.8, 143);
	modelStack.Scale(3.4, 4.4, 3.4);
	RenderMesh(meshList[GEO_SPACEGUY], true, toggleLight);
	modelStack.PopMatrix();

	//SPACESUIT
	modelStack.PushMatrix();
	modelStack.Translate(220, SuitTranslate, 190);
	modelStack.Scale(1.3, 1.3, 1.3);
	modelStack.Rotate(180, 0, 1, 0);
	RenderMesh(meshList[GEO_SPACESUIT], true, toggleLight);
	modelStack.PopMatrix();

	//WINDOW1
	glBlendFunc(1, 1);
	modelStack.PushMatrix();
	modelStack.Translate(220, 16, 209.3);
	modelStack.Scale(2, 2, 2);
	modelStack.Rotate(180, 0, 1, 0);
	RenderMesh(meshList[GEO_WINDOW], true, toggleLight);
	modelStack.PopMatrix();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	//WINDOW2
	glBlendFunc(1, 1);
	modelStack.PushMatrix();
	modelStack.Translate(220, 16, 212);
	modelStack.Scale(2, 2, 2);
	modelStack.Rotate(180, 0, 1, 0);
	RenderMesh(meshList[GEO_WINDOW], true, toggleLight);
	modelStack.PopMatrix();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//HUD
	modelStack.PushMatrix();
	modelStack.Translate(200.5, 16, 190);
	modelStack.Scale(2, 2, 2);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Rotate(180, 0, 1, 0);
	RenderMesh(meshList[GEO_HUD], true, toggleLight);
	modelStack.PopMatrix();
}

void SP2::RenderCafeRoom()
{
	//COUNTER
	modelStack.PushMatrix();
	modelStack.Translate(280, 2, 0);
	modelStack.Scale(2.3, 2, 2.3);
	RenderMesh(meshList[GEO_COUNTER], true, toggleLight);
	modelStack.PopMatrix();

	//FRIDGE
	modelStack.PushMatrix();
	modelStack.Translate(295, 2, -13);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_FRIDGE], true, toggleLight);
	modelStack.PopMatrix();

	//CHEF
	modelStack.PushMatrix();
	modelStack.Translate(280, 2, -2);
	modelStack.Scale(3.5, 3.8, 3.5);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_CHEF], true, toggleLight);
	modelStack.PopMatrix();

	//TABLE
	modelStack.PushMatrix();
	modelStack.Translate(280, 2, 65);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_TABLE], true, toggleLight);
	modelStack.PopMatrix();

	////CHAIR 1
	//modelStack.PushMatrix();
	//modelStack.Translate(270, 2, 65);
	//modelStack.Scale(2, 2, 2);
	//RenderMesh(meshList[GEO_CHAIR], true, toggleLight);
	//modelStack.PopMatrix();

	////CHAIR 2
	//modelStack.PushMatrix();
	//modelStack.Translate(290, 2, 65);
	//modelStack.Scale(2, 2, 2);
	//modelStack.Rotate(180, 0, 1, 0);
	//RenderMesh(meshList[GEO_CHAIR], true, toggleLight);
	//modelStack.PopMatrix();

	//TOKEN
	modelStack.PushMatrix();
	modelStack.Translate(276, TokenTranslate, 61);
	modelStack.Scale(1, 1.5, 1);
	RenderMesh(meshList[GEO_TOKEN], true, toggleLight);
	modelStack.PopMatrix();

	//VENDING
	modelStack.PushMatrix();
	modelStack.Translate(210, 2, 88);
	modelStack.Scale(2.5, 2.5, 2.5);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_VENDING], true, toggleLight);
	modelStack.PopMatrix();

	//NPC
	modelStack.PushMatrix();
	modelStack.Translate(220, 2, -10);
	modelStack.Scale(3.7, 4, 3.7);
	RenderMesh(meshList[GEO_SHOPKEEPER], true, toggleLight);
	modelStack.PopMatrix();
}

void SP2::RenderCrystals()
{
	for (int i = 0; i < CrystalNo; i++)
	{
		if ((((xcoords[i] > 30) && (xcoords[i] < 350)) && ((zcoords[i] > -190) && (zcoords[i] < 250))) || (rendercrystal[i] == 0))
		{

		}
		else
		{
			modelStack.PushMatrix();
			modelStack.Translate(xcoords[i], 2, zcoords[i]);
			modelStack.Scale(5, 5, 5);
			RenderMesh(meshList[GEO_CRYSTAL], true, toggleLight);
			modelStack.PopMatrix();
		}
	}


}

void SP2::RenderApple()
{
	modelStack.PushMatrix();
	modelStack.Translate(266, 12.4, -0.5);
	modelStack.Scale(0.4, 0.4, 0.4);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_APPLE], true, toggleLight);
	modelStack.PopMatrix();

}

void SP2::RenderCoffee()
{
	modelStack.PushMatrix();
	modelStack.Translate(266, 12, -0.5);
	modelStack.Scale(0.5, 0.5, 0.5);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_COFFEE], true, toggleLight);
	modelStack.PopMatrix();

}

void SP2::RenderBread()
{
	modelStack.PushMatrix();
	modelStack.Translate(267, 11, -0.5);
	modelStack.Scale(1.2, 1.2, 1.2);
	RenderMesh(meshList[GEO_BREAD], true, toggleLight);
	modelStack.PopMatrix();

}

void SP2::RenderInstructionBoxOnScreen(Mesh* mesh, float size, float x, float y)
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -100, 100); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);
	RenderMesh(mesh, false, toggleLight);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
}

void SP2::RenderNPCTextBoxOnScreen(Mesh* mesh, float size, float x, float y)
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -100, 100); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);
	RenderMesh(mesh, false, toggleLight);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

}

void SP2::RenderGunOnScreen(Mesh* mesh, float size, float x, float y)
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -500, 500); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);
	modelStack.Rotate(10, 1, 0, 0);
	modelStack.Rotate(-70, 0, 1, 0);
	RenderMesh(mesh, false, toggleLight);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
}

void SP2::RenderPickaxeOnScreen(Mesh* mesh, float size, float x, float y)
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -100, 100); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);
	modelStack.Rotate(-75, 0, 1, 0);
	modelStack.Rotate(34, 0, 0, 1);
	modelStack.Rotate(-90, 0, 0, 1);
	RenderMesh(mesh, true, toggleLight);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
}

void SP2::RenderCafePointerOnScreen(Mesh* mesh, float size, float x, float y)
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);
	modelStack.Rotate(90, 0, 0, 1);
	RenderMesh(mesh, false, toggleLight);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

}

void SP2::RenderShopPointerOnScreen(Mesh* mesh, float size, float x, float y)
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);
	modelStack.Rotate(90, 0, 0, 1);
	RenderMesh(mesh, false, toggleLight);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
}

void SP2::RenderPointerOnScreen(Mesh* mesh, float size, float x, float y)
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);
	//modelStack.Rotate(30, 0, 1, 0);
	RenderMesh(mesh, false, toggleLight);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

}

void SP2::RenderWeaponOnScreen(Mesh* mesh, float size, float x, float y)
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);
	modelStack.Rotate(30, 0, 1, 0);
	RenderMesh(mesh, false, toggleLight);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();


}

void SP2::RenderAsteroids()
{
	for (int i = 0; i < AsteroidNo; i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(asteroidx[i], asteroidy[i], asteroidz[i]);
		modelStack.Scale(20, 20, 20);
		modelStack.Rotate(rotatex[i], 1, 0, 0);
		modelStack.Rotate(rotatez[i], 0, 0, 1);
		RenderMesh(meshList[GEO_ASTEROID], true, toggleLight);
		modelStack.PopMatrix();
	}
}

void SP2::RenderHealthBarOnScreen(Mesh* mesh, float size, float x, float y)
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);
	RenderMesh(mesh, false, toggleLight);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
}

void SP2::RenderTokenOnScreen(Mesh* mesh, float size, float x, float y)
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	RenderMesh(mesh, true, toggleLight);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
}

void SP2::RenderCokeOnScreen(Mesh* mesh, float size, float x, float y)
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(mesh, true, toggleLight);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
}

void SP2::RenderShopTextboxOnScreen(Mesh* mesh, float size, float x, float y)
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);
	modelStack.Rotate(90, 0, 0, 1);
	RenderMesh(mesh, false, toggleLight);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
}

void SP2::RenderCafeTextboxOnScreen(Mesh* mesh, float size, float x, float y)
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);
	modelStack.Rotate(90, 0, 0, 1);
	RenderMesh(mesh, false, toggleLight);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
}

void SP2::RenderHandOnScreen(Mesh* mesh, float size, float x, float y)
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -500, 500); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);
	//modelStack.Rotate(-20, 0, 1, 0);
	//modelStack.Rotate(-30, 1, 0, 0);
	modelStack.Rotate(-35, 1, 0, 0);
	modelStack.Rotate(-30, 0, 0, 1);
	modelStack.Rotate(-33, 0, 1, 0);
	modelStack.Rotate(-270, 1, 0, 0);
	RenderMesh(mesh, false, toggleLight);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
}

void SP2::RenderHandOnScreen2(Mesh* mesh, float size, float x, float y)
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -500, 500); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);
	//modelStack.Rotate(-20, 0, 1, 0);
	////modelStack.Rotate(-30, 1, 0, 0);
	modelStack.Rotate(-35, 1, 0, 0);
	modelStack.Rotate(30, 0, 0, 1);
	modelStack.Rotate(33, 0, 1, 0);
	modelStack.Rotate(-270, 1, 0, 0);
	RenderMesh(mesh, false, toggleLight);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
}

void SP2::RenderSpacemaskOnScreen(Mesh* mesh, float size, float x, float y)
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -500, 500); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);
	//modelStack.Rotate(-20, 0, 1, 0);
	//modelStack.Rotate(90, 1, 0, 0);
	RenderMesh(mesh, true, toggleLight);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
}

void SP2::RenderInventoryOnScreen(Mesh* mesh, float size, float x, float y)
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -500, 500); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);
	RenderMesh(mesh, false, toggleLight);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
}

void SP2::RenderRecRoom()
{
	//SOFA
	modelStack.PushMatrix();
	modelStack.Translate(150, 5, 75);
	modelStack.Scale(5, 8, 5);
	RenderMesh(meshList[GEO_SOFA], true, toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(145, 3, 60);
	modelStack.Scale(2, 1, 2);
	RenderMesh(meshList[GEO_TABLE], true, toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(160, 5, 60);
	modelStack.Scale(5, 8, 5);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_SOFA], true, toggleLight);

	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(145, 10, 60);
	modelStack.Scale(3, 3, 3);
	modelStack.Rotate(180, 0, 1, 0);
	RenderMesh(meshList[GEO_SPEAKERS], true, toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(162, 5, -7);
	modelStack.Scale(5, 7, 2);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_SOFA], true, toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(162, 5, 7);
	modelStack.Scale(5, 7, 2);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_SOFA], true, toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(142, 5, -7);
	modelStack.Scale(5, 7, 2);
	modelStack.Rotate(270, 0, 1, 0);
	RenderMesh(meshList[GEO_SOFA], true, toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(142, 5, 7);
	modelStack.Scale(5, 7, 2);
	modelStack.Rotate(270, 0, 1, 0);
	RenderMesh(meshList[GEO_SOFA], true, toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(82, 2, 87);
	modelStack.Scale(2.5, 2.5, 2.5);
	modelStack.Rotate(270, 0, 1, 0);
	RenderMesh(meshList[GEO_VENDING], true, toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(90, 5, -12);
	modelStack.Scale(5, 8, 5);
	modelStack.Rotate(180, 0, 1, 0);
	RenderMesh(meshList[GEO_SOFA], true, toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(75, 5, 6);
	modelStack.Scale(5, 8, 5);
	modelStack.Rotate(270, 0, 1, 0);
	RenderMesh(meshList[GEO_SOFA], true, toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(91, 3, 6);
	modelStack.Scale(2, 1, 2);
	modelStack.Rotate(270, 0, 1, 0);
	RenderMesh(meshList[GEO_TABLE], true, toggleLight);
	modelStack.PopMatrix();

	//SPACEMAN
	modelStack.PushMatrix();
	modelStack.Translate(105, 2.8, 5);
	modelStack.Scale(3.4, 4.3, 3.4);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_SPACEGUY], true, toggleLight);
	modelStack.PopMatrix();


}

void SP2::RenderScienceLab()
{
	MS *m = &modelStack;

	m->PushMatrix();
	{
		if (Application::IsKeyPressed(VK_NUMPAD0))
		{
			bool debug = true;
		}

		const float delta = 0.1f;

		static float a = 1;
		if (Application::IsKeyPressed(VK_NUMPAD4))
			a += delta;
		if (Application::IsKeyPressed(VK_NUMPAD1))
			a -= delta;

		static float b = 0;
		if (Application::IsKeyPressed(VK_NUMPAD5))
			b += delta;
		if (Application::IsKeyPressed(VK_NUMPAD2))
			b -= delta;

		static float c = 1;
		if (Application::IsKeyPressed(VK_NUMPAD6))
			c += delta;
		if (Application::IsKeyPressed(VK_NUMPAD3))
			c -= delta;

		m->Translate(120, 2, -100);

		m->PushMatrix();
		{
			//Cupboard origin
			m->Translate(30.5f, 0, -45);

			//Beaker 1
			m->PushMatrix();
			{
				m->Translate(8.5f, 9.6f, 0.5f);
				m->Rotate(-32, 0, 1, 0);
				m->Scale(1.9f, 1.9f, 1.9f);
				RenderMesh(meshList[GEO_SCIENCELAB_BEAKER], false, toggleLight);
			}
			m->PopMatrix();

			//Beaker 2
			m->PushMatrix();
			{
				m->Translate(-6.2f, 15.75f, 1.3f);
				m->Rotate(25, 0, 1, 0);
				m->Scale(1.9f, 1.9f, 1.9f);
				RenderMesh(meshList[GEO_SCIENCELAB_BEAKER], false, toggleLight);
			}
			m->PopMatrix();

			m->Rotate(270, 0, 1, 0);
			m->Scale(5.6f, 5.6f, 5.6f);
			RenderMesh(meshList[GEO_SCIENCELAB_CUPBOARD], false, toggleLight);
		}
		m->PopMatrix();

		m->PushMatrix();
		{
			m->Translate(16.6f, 0, 2.3f);
			m->Rotate(0, 0, 1, 0);
			m->Scale(4.5f, 4.5f, 4.5f);
			RenderMesh(meshList[GEO_SCIENCELAB_TABLE], false, toggleLight);
		}
		m->PopMatrix();

		m->PushMatrix();
		{
			m->Translate(-17.8f, 0, -2.3f);
			m->Rotate(0, 0, 1, 0);
			m->Scale(4.5f, 4.5f, 4.5f);
			RenderMesh(meshList[GEO_SCIENCELAB_TABLE], false, toggleLight);
		}
		m->PopMatrix();
	}
	m->PopMatrix();
}

void SP2::RenderCrystalOnScreen(Mesh* mesh, float size, float x, float y)
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);
	RenderMesh(mesh, true, toggleLight);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

}

void SP2::RenderArmouryAndShop()
{
	// Gun Rack + Gun
	modelStack.PushMatrix();

	// Gun Rack
	modelStack.Translate(40, 0, 40);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(6, 6, 6);
	RenderMesh(meshList[GEO_GUN_RACK], true, toggleLight);

	// Gun
	modelStack.PushMatrix();
	modelStack.Scale(0.8, 0.8, 0.8);
	RenderMesh(meshList[GEO_GUN], true, toggleLight);
	modelStack.PopMatrix();

	modelStack.PopMatrix();

	// Shop
	modelStack.PushMatrix();
	modelStack.Translate(30, 0, -35);
	modelStack.Scale(12, 15, 12);
	RenderMesh(meshList[GEO_SHOP], true, toggleLight);
	modelStack.PopMatrix();

	// Shooting Range + Target
	modelStack.PushMatrix();

	// Shooting Range
	modelStack.PushMatrix();
	modelStack.Translate(5, 0, 38);
	modelStack.Scale(6, 6, 6);
	RenderMesh(meshList[GEO_SHOOTING_RANGE], true, toggleLight);
	modelStack.PopMatrix();

	// Target
	modelStack.PushMatrix();
	modelStack.Translate(-35, 0, 38);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(6, 6, 6);
	RenderMesh(meshList[GEO_TARGET], true, toggleLight);
	modelStack.PopMatrix();

	//TRADER
	modelStack.PushMatrix();
	modelStack.Translate(25, 0, -35);
	modelStack.Scale(3.7, 4, 3.7);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_TRADER], true, toggleLight);
	modelStack.PopMatrix();

	//SOLDIER
	modelStack.PushMatrix();
	modelStack.Translate(28, 0, 40);
	modelStack.Scale(3.7, 4, 3.7);
	modelStack.Rotate(180, 0, 1, 0);
	//modelStack.Rotate(90, 0, 1, 0);
	//modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_SOLDIER], true, toggleLight);
	modelStack.PopMatrix();

	modelStack.PopMatrix();
}

void SP2::RenderInfirmary()
{
	modelStack.PushMatrix();
	modelStack.Translate(40, 0, 30);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[GEO_BED], true, toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(20, 0, 30);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[GEO_BED], true, toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-40, 0, 30);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[GEO_BED], true, toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-20, 0, 30);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[GEO_BED], true, toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-30, 15, -30);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[GEO_HEALING_TUBE], true, toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(40, 0, -30);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[GEO_BED], true, toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(20, 0, -30);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[GEO_BED], true, toggleLight);
	modelStack.PopMatrix();

	//NURSE
	modelStack.PushMatrix();
	modelStack.Translate(11, 0, 30);
	modelStack.Scale(3.5, 3.8, 3.5);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_NURSE], true, toggleLight);
	modelStack.PopMatrix();

	//DOCTOR
	modelStack.PushMatrix();
	modelStack.Translate(-18, 0, -30);
	modelStack.Scale(3.5, 3.8, 3.5);
	RenderMesh(meshList[GEO_DOCTOR], true, toggleLight);
	modelStack.PopMatrix();
}

void SP2::RenderTradingStation()
{
	//TRADING STATION
	modelStack.PushMatrix();
	modelStack.Translate(-5, 0, 5);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_TRADEPOST], true, toggleLight);
	modelStack.PopMatrix();
}

void SP2::RenderSpaceShip()
{
	// Start of SpaceShip
	modelStack.PushMatrix();

	modelStack.Translate(shipPos.x, shipPos.y, shipPos.z);

	// Rotate Ship By its own Axis
	modelStack.Rotate(shipHorizontalRotateAngle, 0, 1, 0);
	modelStack.Rotate(shipVerticalRotateAngle, 1, 0, 0);

	// Scale Ship
	modelStack.Scale(4, 4, 4);

	RenderMesh(meshList[GEO_HULL], true, toggleLight);
	RenderMesh(meshList[GEO_WINGS], true, toggleLight);
	RenderMesh(meshList[GEO_ENGINE], true, toggleLight);

	modelStack.PopMatrix();
	// End of Ship
}

void SP2::renderMountains()
{

	for (int zAxis = 500; zAxis >= -500; zAxis -= 100)
	{
		// Boundary Between Base & Maze
		modelStack.PushMatrix();
		modelStack.Translate(-160, 0, zAxis);
		modelStack.Scale(5, 5, 5);
		RenderMesh(meshList[GEO_MOUNTAIN], true, toggleLight);
		modelStack.PopMatrix();

		// Boundary at the Base's Side
		modelStack.PushMatrix();
		modelStack.Translate(550, 0, zAxis);
		modelStack.Scale(5, 5, 5);
		RenderMesh(meshList[GEO_MOUNTAIN], true, toggleLight);
		modelStack.PopMatrix();

		// Boundary at the Maze's Side
		modelStack.PushMatrix();
		modelStack.Translate(-550, 0, zAxis);
		modelStack.Scale(5, 5, 5);
		RenderMesh(meshList[GEO_MOUNTAIN], true, toggleLight);
		modelStack.PopMatrix();
	}

	for (int xAxis = 500; xAxis >= -500; xAxis -= 100)
	{
		// Boundary at the Base's Side
		modelStack.PushMatrix();
		modelStack.Translate(xAxis, 0, 600);
		modelStack.Scale(5, 5, 5);
		RenderMesh(meshList[GEO_MOUNTAIN], true, toggleLight);
		modelStack.PopMatrix();

		// Boundary at the Maze's Side
		modelStack.PushMatrix();
		modelStack.Translate(xAxis, 0, -500);
		modelStack.Scale(5, 5, 5);
		RenderMesh(meshList[GEO_MOUNTAIN], true, toggleLight);
		modelStack.PopMatrix();
	}


}

void SP2::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void SP2::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	//Add these code just after glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);


	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 0.55f + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

	glEnable(GL_DEPTH_TEST);
}