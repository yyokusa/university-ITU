-- USER TABLE
-- Table: public.user

CREATE TABLE IF NOT EXISTS public."user"
(
    id integer NOT NULL GENERATED ALWAYS AS IDENTITY ( INCREMENT 1 START 1 MINVALUE 1 MAXVALUE 2147483647 CACHE 1 ),
    username character varying(30) COLLATE pg_catalog."default" NOT NULL,
    password character varying(256) COLLATE pg_catalog."default" NOT NULL,
    created time(6) with time zone NOT NULL DEFAULT now(),
    email character varying(128) COLLATE pg_catalog."default" NOT NULL,
    name character varying(128) COLLATE pg_catalog."default",
    surname character varying(128) COLLATE pg_catalog."default",
    country_id integer,
    CONSTRAINT user_pkey PRIMARY KEY (id),
    CONSTRAINT email_unique UNIQUE (email),
    CONSTRAINT username_unique UNIQUE (username),
    CONSTRAINT user_country_id_fkey FOREIGN KEY (country_id)
        REFERENCES public.country (id) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION
        NOT VALID
)

-- Table: public.human_development

CREATE TABLE IF NOT EXISTS public.human_development
(
    id integer NOT NULL GENERATED ALWAYS AS IDENTITY ( INCREMENT 1 START 1 MINVALUE 1 MAXVALUE 2147483647 CACHE 1 ),
    country_id integer NOT NULL,
    hdi double precision,
    life double precision,
    education_e double precision,
    education_m double precision,
    gnhd character varying(30) COLLATE pg_catalog."default",
    gni integer,
    CONSTRAINT human_development_pkey PRIMARY KEY (id),
    CONSTRAINT human_development_country_id_fkey FOREIGN KEY (country_id)
        REFERENCES public.country (id) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION
        NOT VALID
)

-- Table: public.historical_index

CREATE TABLE IF NOT EXISTS public.historical_index
(
    "1990" double precision,
    "2000" double precision,
    "2010" double precision,
    "2011" double precision,
    "2012" double precision,
    "2013" double precision,
    id integer NOT NULL GENERATED ALWAYS AS IDENTITY ( INCREMENT 1 START 1 MINVALUE 1 MAXVALUE 2147483647 CACHE 1 ),
    country_id integer NOT NULL,
    CONSTRAINT historical_index_pkey PRIMARY KEY (id),
    CONSTRAINT historical_index_country_id_fkey FOREIGN KEY (country_id)
        REFERENCES public.country (id) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION
)

-- Table: public.country

CREATE TABLE IF NOT EXISTS public.country
(
    name character varying COLLATE pg_catalog."default" NOT NULL,
    hdi_rank integer NOT NULL,
    id integer NOT NULL GENERATED ALWAYS AS IDENTITY ( INCREMENT 1 START 1 MINVALUE 1 MAXVALUE 2147483647 CACHE 1 ),
    CONSTRAINT country_pkey PRIMARY KEY (id)
)
