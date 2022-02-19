-- User TABLE:
--
--     id:     mail:               age: password:   usename:    TYPE:DOCTOR/PATIENT
--                 @healtcare.com
--
-- PATIENT INFO TABLE:
--
--     id    PATIENT (FK):    Doctor (FK):       BLOOD_TYPE:  BLOOD_PRESSURE:    DIAGNOSIS:[1(Pending) 2(HEALTHY) 3(UNHEALTHY) 4() 5()] Time: DATE_TIME
--                 user1              user2
-- Notification TABLE:
--     id  From (FK):          To (FK):           STATUS :PENDİNG CONFIRMED
--                 (PATIENT)           (DOCTOR)
--
-- **This notification table will be used for both DOCTOR and PATIENT, the check operation will be held on in backend part**
-- 2 -> 1
-- 3 -> 1


-- Table: public.user

-- DROP TABLE IF EXISTS public."user";

CREATE TABLE IF NOT EXISTS public."user"
(
    id integer NOT NULL GENERATED ALWAYS AS IDENTITY ( INCREMENT 1 START 1 MINVALUE 1 MAXVALUE 2147483647 CACHE 1 ),
    email character varying(60) COLLATE pg_catalog."default" NOT NULL,
    age smallint,
    name character varying(60) COLLATE pg_catalog."default" NOT NULL,
    surname character varying(60) COLLATE pg_catalog."default" NOT NULL,
    password character varying(300) COLLATE pg_catalog."default" NOT NULL,
    user_type smallint NOT NULL,
    CONSTRAINT user_pkey PRIMARY KEY (id),
    CONSTRAINT email UNIQUE (email)
)

TABLESPACE pg_default;

ALTER TABLE IF EXISTS public."user"
    OWNER to vherwwgycjigkp;


-- Table: public.patient_info

-- DROP TABLE IF EXISTS public.patient_info;

CREATE TABLE IF NOT EXISTS public.patient_info
(
    patient_id integer NOT NULL,
    doctor_id integer NOT NULL,
    blood_type character(10) COLLATE pg_catalog."default",
    blood_pressure character(20) COLLATE pg_catalog."default",
    diagnosis smallint NOT NULL DEFAULT 1,
    "timestamp" timestamp(6) with time zone NOT NULL DEFAULT now(),
    id integer NOT NULL GENERATED ALWAYS AS IDENTITY ( INCREMENT 1 START 1 MINVALUE 1 MAXVALUE 2147483647 CACHE 1 ),
    CONSTRAINT patient_info_pkey PRIMARY KEY (id),
    CONSTRAINT fk_doctor_id FOREIGN KEY (doctor_id)
        REFERENCES public."user" (id) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION,
    CONSTRAINT fk_patient_id FOREIGN KEY (patient_id)
        REFERENCES public."user" (id) MATCH SIMPLE
        ON UPDATE RESTRICT
        ON DELETE NO ACTION
)

TABLESPACE pg_default;

ALTER TABLE IF EXISTS public.patient_info
    OWNER to vherwwgycjigkp;

-- Table: public.notification

-- DROP TABLE IF EXISTS public.notification;

CREATE TABLE IF NOT EXISTS public.notification
(
    id integer NOT NULL GENERATED ALWAYS AS IDENTITY ( INCREMENT 1 START 1 MINVALUE 1 MAXVALUE 2147483647 CACHE 1 ),
    "from" integer NOT NULL,
    "to" integer NOT NULL,
    status boolean NOT NULL DEFAULT false,
    CONSTRAINT notification_pkey PRIMARY KEY (id),
    CONSTRAINT fk_from FOREIGN KEY ("from")
        REFERENCES public."user" (id) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION,
    CONSTRAINT fk_to FOREIGN KEY ("to")
        REFERENCES public."user" (id) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION
)

TABLESPACE pg_default;

ALTER TABLE IF EXISTS public.notification
    OWNER to vherwwgycjigkp;
