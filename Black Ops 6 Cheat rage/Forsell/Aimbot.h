#pragma once
enum boneIndex : int32_t
{
    tag_origin,
    tag_sync,
    j_mainroot,
    j_spinelower,
    j_spineupper,
    j_spine4,
    j_neck,
    j_head,
    j_helmet,
    j_clavicle_le,
    j_shoulder_le,
    j_elbow_le,
    j_wrist_le,
    j_clavicle_ri,
    j_shoulder_ri,
    j_elbow_ri,
    j_wrist_ri,
    j_hip_le,
    j_knee_le,
    j_ankle_le,
    j_ball_le,
    j_hip_ri,
    j_knee_ri,
    j_ankle_ri,
    j_ball_ri,
    tag_stowed_hip_rear,
    j_hiptwist_le,
    j_hiptwist_ri,
    tag_inhand,
    tag_shield_back,
    tag_weapon_chest,
    j_gun_adjust,
    j_gun,
    j_shouldertwist_le,
    j_shouldertwist_ri,
    tag_eye,
    tag_weapon_right,
    j_sheild_ri,
    j_wristfronttwist1_le,
    tag_reflector_arm_le,
    tag_reflector_arm_ri,
    tag_helmetlight,
    tag_accessory_left,
    tag_accessory_right,
    tag_weapon_left,
    tag_ik_wrist_loc_le,
    tag_ik_wrist_loc_ri,
    j_hipholster_le,
    j_hipholster_ri,
    j_hip_proc_le,
    j_hip_proc_ri,
    j_dummy_knee_dist,
    j_spinelower_lift,
    j_proc_spinelower,
    j_proc_spinelower2,
    j_proc_spineupper,
    j_ik_foot_root,
    tag_ik_foot_loc_le,
    tag_ik_foot_loc_ri,
    j_antislide_ik,
    tag_wrist_attach_le,
    j_proc_hip_lift_le,
    j_proc_hip_lift_ri,
    j_proc_hip_lift_aim_le,
    j_proc_hip_lift_aim_ri,
    j_proc_dummy_spinelift,
    j_chest,
    j_dummy_slingcenteraim,
    j_dummy_sling_spine,
    j_groinprotector,
    j_proc_lift_clavicle_le,
    j_proc_lift_clavicle_ri,
    j_proc_stowed_chest,
    j_proc_spinelift,
    j_proc_spinelower_lift,
    j_proc_spineupper_lift,
    j_sling_spine
};



namespace aimbot
{
    extern  bool is_visible(math::vec3_t start, math::vec3_t end, int index);
    extern bool is_key_active();
    extern math::vec3_t	m_best_pos;
   // void NoSpread(game_struct::usercmd_t* cmd);
    float Angle_Normalize(float angle);
    void apply();
    void applyStandard();
    void applySilent();
    //void applypSilent(game_struct::usercmd_t* cmd);
    //void MovementFix(game_struct::usercmd_t* usercmd, float yaw);

    void aim();
    //void aim2(game_struct::usercmd_t* cmd);
    void StandardAim();
    //void SilentAim();
   // void perfectSilentAim(game_struct::usercmd_t* cmd);
    void draw_fov(const float aimbot_fov);
    //void FirstBulletFix();
}

