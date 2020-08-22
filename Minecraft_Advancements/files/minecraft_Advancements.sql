CREATE TABLE IF NOT EXISTS "statistics" ("nom"	TEXT NOT NULL, "valeur"	TEXT NOT NULL, "version"	TEXT NOT NULL);
CREATE TABLE IF NOT EXISTS "list_advancements" (	"id"	INTEGER NOT NULL,	"origine"	TEXT NOT NULL,	"version"	TEXT NOT NULL,	"categorie"	TEXT NOT NULL,	"identifiant"	TEXT NOT NULL,	"titre"	TEXT NOT NULL,	"description"	TEXT,	"condition"	TEXT NOT NULL,	"condition_texte"	TEXT NOT NULL,	"type_condition"	TEXT NOT NULL,	PRIMARY KEY("id" AUTOINCREMENT));
CREATE TABLE IF NOT EXISTS "traduction_vanilla" (	"id"	INTEGER NOT NULL,	"version"	TEXT NOT NULL,	"key"	TEXT NOT NULL,	"value"	TEXT NOT NULL,	PRIMARY KEY("id" AUTOINCREMENT));
CREATE TABLE IF NOT EXISTS "player_advancements" (	"id"	INTEGER NOT NULL,	"version"	TEXT NOT NULL,	"identifiant"	TEXT NOT NULL,	"done"	TEXT NOT NULL,	"condition"	TEXT NOT NULL,	"date_fait"	TEXT NOT NULL,	PRIMARY KEY("id" AUTOINCREMENT));
CREATE UNIQUE INDEX IF NOT EXISTS "index_list_advancements_id" ON "list_advancements" (	"id"	ASC);
CREATE INDEX IF NOT EXISTS "index_list_advancements_identifiant-condition" ON "list_advancements" (	"identifiant"	ASC,	"condition"	ASC);
